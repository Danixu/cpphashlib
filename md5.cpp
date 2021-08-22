/*******************************************************************************
 * 
 * Created by Daniel Carrasco at https://www.electrosoftcloud.com
 * 
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
 *
 ******************************************************************************/

#include "md5.hpp"


cpphashlib::md5::md5() {
    init();
}

cpphashlib::md5::md5(const std::string &text) {
    init();
    update(text.c_str(), text.length());
    finalize();
}

cpphashlib::md5::md5(char *Input, long length) {
    init();
    update(Input, length);
    finalize();
}

void cpphashlib::md5::init() {
    finalized = false;
    
    count[0] = 0;
    count[1] = 0;
    
    // Initialization constants.
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}

void cpphashlib::md5::decode(uint32_t output[], const uint8_t input[], uint32_t len) {
    for (unsigned int i = 0, j = 0; j < len; i++, j += 4) {
        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j+1]) << 8) |
            (((uint32_t)input[j+2]) << 16) | (((uint32_t)input[j+3]) << 24);
    }
}


void cpphashlib::md5::encode(uint8_t output[], const uint32_t input[], uint32_t len) {
  for (uint32_t i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = input[i] & 0xff;
    output[j+1] = (input[i] >> 8) & 0xff;
    output[j+2] = (input[i] >> 16) & 0xff;
    output[j+3] = (input[i] >> 24) & 0xff;
  }
}

void cpphashlib::md5::transform(const uint8_t block[blocksize]) {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    decode (x, block, blocksize);
    
    /* Round 1 */
    FF (a, b, c, d, x[ 0], transforms[ 0], 0xd76aa478); /* 1 */
    FF (d, a, b, c, x[ 1], transforms[ 1], 0xe8c7b756); /* 2 */
    FF (c, d, a, b, x[ 2], transforms[ 2], 0x242070db); /* 3 */
    FF (b, c, d, a, x[ 3], transforms[ 3], 0xc1bdceee); /* 4 */
    FF (a, b, c, d, x[ 4], transforms[ 0], 0xf57c0faf); /* 5 */
    FF (d, a, b, c, x[ 5], transforms[ 1], 0x4787c62a); /* 6 */
    FF (c, d, a, b, x[ 6], transforms[ 2], 0xa8304613); /* 7 */
    FF (b, c, d, a, x[ 7], transforms[ 3], 0xfd469501); /* 8 */
    FF (a, b, c, d, x[ 8], transforms[ 0], 0x698098d8); /* 9 */
    FF (d, a, b, c, x[ 9], transforms[ 1], 0x8b44f7af); /* 10 */
    FF (c, d, a, b, x[10], transforms[ 2], 0xffff5bb1); /* 11 */
    FF (b, c, d, a, x[11], transforms[ 3], 0x895cd7be); /* 12 */
    FF (a, b, c, d, x[12], transforms[ 0], 0x6b901122); /* 13 */
    FF (d, a, b, c, x[13], transforms[ 1], 0xfd987193); /* 14 */
    FF (c, d, a, b, x[14], transforms[ 2], 0xa679438e); /* 15 */
    FF (b, c, d, a, x[15], transforms[ 3], 0x49b40821); /* 16 */
    
    /* Round 2 */
    GG (a, b, c, d, x[ 1], transforms[ 4], 0xf61e2562); /* 17 */
    GG (d, a, b, c, x[ 6], transforms[ 5], 0xc040b340); /* 18 */
    GG (c, d, a, b, x[11], transforms[ 6], 0x265e5a51); /* 19 */
    GG (b, c, d, a, x[ 0], transforms[ 7], 0xe9b6c7aa); /* 20 */
    GG (a, b, c, d, x[ 5], transforms[ 4], 0xd62f105d); /* 21 */
    GG (d, a, b, c, x[10], transforms[ 5],  0x2441453); /* 22 */
    GG (c, d, a, b, x[15], transforms[ 6], 0xd8a1e681); /* 23 */
    GG (b, c, d, a, x[ 4], transforms[ 7], 0xe7d3fbc8); /* 24 */
    GG (a, b, c, d, x[ 9], transforms[ 4], 0x21e1cde6); /* 25 */
    GG (d, a, b, c, x[14], transforms[ 5], 0xc33707d6); /* 26 */
    GG (c, d, a, b, x[ 3], transforms[ 6], 0xf4d50d87); /* 27 */
    GG (b, c, d, a, x[ 8], transforms[ 7], 0x455a14ed); /* 28 */
    GG (a, b, c, d, x[13], transforms[ 4], 0xa9e3e905); /* 29 */
    GG (d, a, b, c, x[ 2], transforms[ 5], 0xfcefa3f8); /* 30 */
    GG (c, d, a, b, x[ 7], transforms[ 6], 0x676f02d9); /* 31 */
    GG (b, c, d, a, x[12], transforms[ 7], 0x8d2a4c8a); /* 32 */
    
    /* Round 3 */
    HH (a, b, c, d, x[ 5], transforms[ 8], 0xfffa3942); /* 33 */
    HH (d, a, b, c, x[ 8], transforms[ 9], 0x8771f681); /* 34 */
    HH (c, d, a, b, x[11], transforms[10], 0x6d9d6122); /* 35 */
    HH (b, c, d, a, x[14], transforms[11], 0xfde5380c); /* 36 */
    HH (a, b, c, d, x[ 1], transforms[ 8], 0xa4beea44); /* 37 */
    HH (d, a, b, c, x[ 4], transforms[ 9], 0x4bdecfa9); /* 38 */
    HH (c, d, a, b, x[ 7], transforms[10], 0xf6bb4b60); /* 39 */
    HH (b, c, d, a, x[10], transforms[11], 0xbebfbc70); /* 40 */
    HH (a, b, c, d, x[13], transforms[ 8], 0x289b7ec6); /* 41 */
    HH (d, a, b, c, x[ 0], transforms[ 9], 0xeaa127fa); /* 42 */
    HH (c, d, a, b, x[ 3], transforms[10], 0xd4ef3085); /* 43 */
    HH (b, c, d, a, x[ 6], transforms[11],  0x4881d05); /* 44 */
    HH (a, b, c, d, x[ 9], transforms[ 8], 0xd9d4d039); /* 45 */
    HH (d, a, b, c, x[12], transforms[ 9], 0xe6db99e5); /* 46 */
    HH (c, d, a, b, x[15], transforms[10], 0x1fa27cf8); /* 47 */
    HH (b, c, d, a, x[ 2], transforms[11], 0xc4ac5665); /* 48 */
    
    /* Round 4 */
    II (a, b, c, d, x[ 0], transforms[12], 0xf4292244); /* 49 */
    II (d, a, b, c, x[ 7], transforms[13], 0x432aff97); /* 50 */
    II (c, d, a, b, x[14], transforms[14], 0xab9423a7); /* 51 */
    II (b, c, d, a, x[ 5], transforms[15], 0xfc93a039); /* 52 */
    II (a, b, c, d, x[12], transforms[12], 0x655b59c3); /* 53 */
    II (d, a, b, c, x[ 3], transforms[13], 0x8f0ccc92); /* 54 */
    II (c, d, a, b, x[10], transforms[14], 0xffeff47d); /* 55 */
    II (b, c, d, a, x[ 1], transforms[15], 0x85845dd1); /* 56 */
    II (a, b, c, d, x[ 8], transforms[12], 0x6fa87e4f); /* 57 */
    II (d, a, b, c, x[15], transforms[13], 0xfe2ce6e0); /* 58 */
    II (c, d, a, b, x[ 6], transforms[14], 0xa3014314); /* 59 */
    II (b, c, d, a, x[13], transforms[15], 0x4e0811a1); /* 60 */
    II (a, b, c, d, x[ 4], transforms[12], 0xf7537e82); /* 61 */
    II (d, a, b, c, x[11], transforms[13], 0xbd3af235); /* 62 */
    II (c, d, a, b, x[ 2], transforms[14], 0x2ad7d2bb); /* 63 */
    II (b, c, d, a, x[ 9], transforms[15], 0xeb86d391); /* 64 */
    
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    
    // Zeroize sensitive information.
    memset(x, 0, sizeof x);
}


void cpphashlib::md5::update(const unsigned char input[], uint32_t length) {
  // compute number of bytes mod 64
  uint32_t index = count[0] / 8 % blocksize;
 
  // Update number of bits
  if ((count[0] += (length << 3)) < (length << 3))
    count[1]++;
  count[1] += (length >> 29);
 
  // number of bytes we need to fill in buffer
  uint32_t firstpart = 64 - index;
 
  uint32_t i;
 
  // transform as many times as possible.
  if (length >= firstpart)
  {
    // fill buffer first, transform
    memcpy(&buffer[index], input, firstpart);
    transform(buffer);
 
    // transform chunks of blocksize (64 bytes)
    for (i = firstpart; i + blocksize <= length; i += blocksize)
      transform(&input[i]);
 
    index = 0;
  }
  else
    i = 0;
 
  // buffer remaining input
  memcpy(&buffer[index], &input[i], length-i);
}
 

void cpphashlib::md5::update(const char input[], uint32_t length) {
    update((const unsigned char*)input, length);
}
 

void cpphashlib::md5::finalize() {
    static unsigned char padding[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    
    if (!finalized) {
        // Save number of bits
        unsigned char bits[8];
        encode(bits, count, 8);
    
        // pad out to 56 mod 64.
        uint32_t index = count[0] / 8 % 64;
        uint32_t padLen = (index < 56) ? (56 - index) : (120 - index);
        update(padding, padLen);
    
        // Append length (before padding)
        update(bits, 8);
    
        // Store state in digest
        encode(digest, state, 16);
    
        // Zeroize sensitive information.
        memset(buffer, 0, sizeof buffer);
        memset(count, 0, sizeof count);
    
        finalized = true;
    }
}

std::string cpphashlib::md5::hexdigest() const {
  if (!finalized)
    return "";
 
  char buf[33];
  for (int i=0; i<16; i++)
    sprintf(buf+i*2, "%02x", digest[i]);
  buf[32]=0;
 
  return std::string(buf);
}