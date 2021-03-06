// Copyright 2018 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "uintBig.h"

namespace beam {


	char ChFromHex(uint8_t v)
	{
		return v + ((v < 10) ? '0' : ('a' - 10));
	}

	void uintBigImpl::_Print(const uint8_t* pDst, uint32_t nDst, std::ostream& s)
	{
		const uint32_t nDigitsMax = 8;
		if (nDst > nDigitsMax)
			nDst = nDigitsMax; // truncate

		char sz[nDigitsMax * 2 + 1];

		for (uint32_t i = 0; i < nDst; i++)
		{
			sz[i * 2] = ChFromHex(pDst[i] >> 4);
			sz[i * 2 + 1] = ChFromHex(pDst[i] & 0xf);
		}

		sz[nDst << 1] = 0;
		s << sz;
	}

	void uintBigImpl::_Assign(uint8_t* pDst, uint32_t nDst, const uint8_t* pSrc, uint32_t nSrc)
	{
		if (nSrc >= nDst)
			memcpy(pDst, pSrc + nSrc - nDst, nDst);
		else
		{
			memset0(pDst, nDst - nSrc);
			memcpy(pDst + nDst - nSrc, pSrc, nSrc);
		}
	}

	uint8_t uintBigImpl::_Inc(uint8_t* pDst, uint32_t nDst)
	{
		for (uint32_t i = nDst; i--; )
			if (++pDst[i])
				return 0;

		return 1;
	}

	uint8_t uintBigImpl::_Inc(uint8_t* pDst, uint32_t nDst, const uint8_t* pSrc)
	{
		uint16_t carry = 0;
		for (uint32_t i = nDst; i--; )
		{
			carry += pDst[i];
			carry += pSrc[i];

			pDst[i] = (uint8_t) carry;
			carry >>= 8;
		}

		return (uint8_t) carry;
	}

	uint8_t uintBigImpl::_Inc(uint8_t* pDst, uint32_t nDst, const uint8_t* pSrc, uint32_t nSrc)
	{
		if (nDst <= nSrc)
			return _Inc(pDst, nDst, pSrc + nSrc - nDst); // src is at least our size

		if (!_Inc(pDst + nDst - nSrc, nSrc, pSrc))
			return 0;

		// propagete carry
		return _Inc(pDst, nDst - nSrc);
	}

	void uintBigImpl::_Inv(uint8_t* pDst, uint32_t nDst)
	{
		for (uint32_t i = nDst; i--; )
			pDst[i] ^= 0xff;
	}

	void uintBigImpl::_Xor(uint8_t* pDst, uint32_t nDst, const uint8_t* pSrc)
	{
		for (uint32_t i = nDst; i--; )
			pDst[i] ^= pSrc[i];
	}

	void uintBigImpl::_Xor(uint8_t* pDst, uint32_t nDst, const uint8_t* pSrc, uint32_t nSrc)
	{
		if (nDst <= nSrc)
			_Xor(pDst, nDst, pSrc + nSrc - nDst); // src is at least our size
		else
			_Xor(pDst + nDst - nSrc, nSrc, pSrc);
	}

	void uintBigImpl::_Mul(uint8_t* pDst, uint32_t nDst, const uint8_t* pSrc0, uint32_t nSrc0, const uint8_t* pSrc1, uint32_t nSrc1)
	{
		memset0(pDst, nDst);

		if (nSrc0 > nDst)
		{
			pSrc0 += nSrc0 - nDst;
			nSrc0 = nDst;
		}

		if (nSrc1 > nDst)
		{
			pSrc1 += nSrc1 - nDst;
			nSrc1 = nDst;
		}

		int32_t nDelta = nSrc0 + nSrc1 - nDst - 1;

		for (uint32_t i0 = nSrc0; i0--; )
		{
			uint8_t x0 = pSrc0[i0];
			uint16_t carry = 0;

			uint32_t iDst = i0 - nDelta; // don't care if overflows
			uint32_t i1Min = (iDst > nDst) ? (-static_cast<int32_t>(iDst)) : 0;
			for (uint32_t i1 = nSrc1; i1-- > i1Min; )
			{
				uint8_t& dst = pDst[iDst + i1];

				uint16_t x1 = pSrc1[i1];
				x1 *= x0;
				carry += x1;
				carry += dst;

				dst = (uint8_t) carry;
				carry >>= 8;
			}

			if (iDst <= nDst)
				while (carry && iDst--)
				{
					uint8_t& dst = pDst[iDst];
					carry += dst;

					dst = (uint8_t) carry;
					carry >>= 8;
				}
		}
	}

	int uintBigImpl::_Cmp(const uint8_t* pSrc0, uint32_t nSrc0, const uint8_t* pSrc1, uint32_t nSrc1)
	{
		if (nSrc0 > nSrc1)
		{
			uint32_t diff = nSrc0 - nSrc1;
			if (!memis0(pSrc0, diff))
				return 1;

			pSrc0 += diff;
			nSrc0 = nSrc1;
		} else
			if (nSrc0 < nSrc1)
			{
				uint32_t diff = nSrc1 - nSrc0;
				if (!memis0(pSrc1, diff))
					return -1;

				pSrc1 += diff;
			}

		return memcmp(pSrc0, pSrc1, nSrc0);
	}

	uint32_t uintBigImpl::_GetOrder(const uint8_t* pDst, uint32_t nDst)
	{
		for (uint32_t nByte = 0; ; nByte++)
		{
			if (nDst == nByte)
				return 0; // the number is zero

			uint8_t x = pDst[nByte];
			if (!x)
				continue;

			uint32_t nOrder = ((nDst - nByte) << 3) - 7;
			while (x >>= 1)
				nOrder++;

			return nOrder;
		}

	}

	bool uintBigImpl::_Accept(uint8_t* pDst, const uint8_t* pThr, uint32_t nDst, uint32_t nThrOrder)
	{
		if (!nThrOrder)
			return false;

		nThrOrder--;
		uint32_t nOffs = nDst - 1 - (nThrOrder >> 3);
		uint8_t msk = uint8_t(2 << (7 & nThrOrder)) - 1;
		assert(msk);

		pDst[nOffs] &= msk;

		if (memcmp(pDst + nOffs, pThr + nOffs, nDst - nOffs) >= 0)
			return false;

		memset0(pDst, nOffs);
		return true;
	}

} // namespace beam
