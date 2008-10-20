/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <assert.h>

std::string base64_encode(const std::string& src)
{
  static const char base64_table[] =
    {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/"
    };
  std::string dst;
  dst.reserve(((src.size()+2)/3)*4);
  for(unsigned src_pos = 0; src_pos < src.size(); src_pos += 3)
    {
      const unsigned filling =
        (src_pos + 3)>src.size() ?
            src.size() - src_pos :
        3;

        dst += base64_table[unsigned(src[src_pos + 0] & 0xFC) >> 2]; // FC = 11111100
        if(filling == 1)
          {
            dst += base64_table[((src[src_pos + 0] & 0x03) << 4)]; // 03 = 11
            dst += '=';
            dst += '=';
          }
        else if(filling == 2)
          {
            dst += base64_table[((src[src_pos + 0] & 0x03) << 4) | (unsigned(src[src_pos + 1] & 0xF0) >> 4)]; // 03 = 11
            dst += base64_table[((src[src_pos + 1] & 0x0F) << 2) | (unsigned(src[src_pos + 2] & 0xC0) >> 6)]; // 0F = 1111, C0=11110
            dst += '=';
          }
        else
          {
            assert(filling == 3);
            dst += base64_table[((src[src_pos + 0] & 0x03) << 4) | (unsigned(src[src_pos + 1] & 0xF0) >> 4)]; // 03 = 11
            dst += base64_table[((src[src_pos + 1] & 0x0F) << 2) | (unsigned(src[src_pos + 2] & 0xC0) >> 6)]; // 0F = 1111, C0=11110
            dst += base64_table[src[src_pos + 2] & 0x3F]; // 3F = 111111
          }
    }
  return dst;
}
