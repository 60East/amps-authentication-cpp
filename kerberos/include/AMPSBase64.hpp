////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012-2018 60East Technologies Inc., All Rights Reserved.
//
// This computer software is owned by 60East Technologies Inc. and is
// protected by U.S. copyright laws and other laws and by international
// treaties.  This computer software is furnished by 60East Technologies
// Inc. pursuant to a written license agreement and may be used, copied,
// transmitted, and stored only in accordance with the terms of such
// license agreement and with the inclusion of the above copyright notice.
// This computer software or any other copies thereof may not be provided
// or otherwise made available to any other person.
//
// U.S. Government Restricted Rights.  This computer software: (a) was
// developed at private expense and is in all respects the proprietary
// information of 60East Technologies Inc.; (b) was not developed with
// government funds; (c) is a trade secret of 60East Technologies Inc.
// for all purposes of the Freedom of Information Act; and (d) is a
// commercial item and thus, pursuant to Section 12.212 of the Federal
// Acquisition Regulations (FAR) and DFAR Supplement Section 227.7202,
// Government's use, duplication or disclosure of the computer software
// is subject to the restrictions set forth by 60East Technologies Inc.
//
////////////////////////////////////////////////////////////////////////////

#ifndef _AMPS_BASE64_HPP_
#define _AMPS_BASE64_HPP_

namespace AMPS
{
  namespace Base64
  {

    static std::string encode(const std::string& in)
    {

      std::string out;

      int val = 0, valb = -6;
      for (unsigned char c : in)
      {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0)
        {
          out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
          valb -= 6;
        }
      }
      if (valb > -6)
      {
        out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
      }
      while (out.size() % 4)
      {
        out.push_back('=');
      }
      return out;
    }

    static std::string decode(const std::string& in)
    {

      std::string out;

      std::vector<int> T(256, -1);
      for (int i = 0; i < 64; i++)
      {
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
      }

      int val = 0, valb = -8;
      for (unsigned char c : in)
      {
        if (T[c] == -1)
        {
          break;
        }
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
          out.push_back(char((val >> valb) & 0xFF));
          valb -= 8;
        }
      }
      return out;
    }

  } // end namespace Base64
} // end namespace AMPS

#endif
