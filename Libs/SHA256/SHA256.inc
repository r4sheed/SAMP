/****************************************************************************************************
 *                                                                                                  *
 *                                         )(   SHA256   )(                                         *
 *                                                                                                  *
 * Copyright © 2021 National Security Agency. All rights reserved.                                  *
 * Contributors: dwd222, Abyss Morgan                                                               *
 *                                                                                                  *
 * Website: https://adm.ct8.pl                                                                      *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.0.0                                                                              *
 *                                                                                                  *
 * Functions:                                                                                       *
 * SHA256::Hash(str[]);                                                                             *
 * SHA256::HashFile(const file_name[],position=0,max_len=cellmax);                                  *
 *                                                                                                  *
 * Extended Functions:                                                                              *
 * SHA256::UINT8ToBit(value);                                                                       *
 * SHA256::UINT64ToBit(value);                                                                      *
 * SHA256::BitToUINT32(str[]);                                                                      *
 * SHA256::TextToBit(text[],bittext[],len);                                                         *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _SHA256_HASH
	#endinput
#endif
#define _SHA256_HASH

#define SHA256::			SHA256_

stock SHA256::UINT8ToBit(value){
	new str[] = "00000000", i = 7;
	while(value){
	    str[i] = (value % 2) + 48;
	    value = value/2;
		i--;
	}
	return str;
}

stock SHA256::UINT64ToBit(value){
	new str[] = "0000000000000000000000000000000000000000000000000000000000000000", i = 63;
	while(value){
	    str[i] = (value % 2) + 48;
	    value = value/2;
		i--;
	}
	return str;
}

stock SHA256::BitToUINT32(str[]){
	new results = 0, j, fx = 0, len = strlen(str);
	if(len > 32) len = 32;
	j = len - 1;
	while(str[j] && j > -1){
	    results += (str[j--] - 48) * floatround(floatpower(2, fx));
	    fx++;
	}
	return results;
}

stock SHA256::TextToBit(text[], bittext[], len){
	new i = 0, n = 0;
	while(text[i] && n < len){
	    new j = 0;
	    new tmp[9];
		tmp = SHA256::UINT8ToBit(text[i++]);
		while(tmp[j]) bittext[n++] = tmp[j++];
	}
	bittext[n] = '\0';
	return n;
}

stock SHA256::RotateRight(value, rot){
	return (value >>> rot) | (value << (32 - rot));
}

stock SHA256::Hash(str[]){
    new H[] =  {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	new k[] =  {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
				0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
				0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
				0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
				0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
				0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
				0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
				0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

 	new it, length = strlen(str) * 8;
	length++;
	while((length%512) != 448){
	    length++;
	}
	length += 64;
	it = (length/512);
	
	for(new n = 0; n < it; n++){
	    new sha_256[128*4+1], s0, s1, w[64] = 0;
	 	new len = SHA256::TextToBit(str[n*64], sha_256, 512);
		if(len < 512){
			sha_256[len++] = '1';

			while((len%512) != 448){
			    sha_256[len++] = '0';
			}
			new tmp[65];
			tmp = SHA256::UINT64ToBit(strlen(str) * 8);
			new i = 0;
			while(tmp[i]){
				sha_256[len++] = tmp[i++];
			}
			sha_256[len] = '\0';
		}

  		new a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
		new j = 32;
		for(new x = 0; x < 16; x++){
			w[x] = SHA256::BitToUINT32(sha_256[(j*x)]);
		}
		for(new i = 16; i <= 63; i++){
			s0 = SHA256::RotateRight(w[i - 15], 7)^SHA256::RotateRight(w[i - 15], 18)^(w[i - 15] >>> 3);
			s1 = SHA256::RotateRight(w[i - 2], 17)^SHA256::RotateRight(w[i - 2], 19)^(w[i - 2] >>> 10);
			w[i] = (w[i - 16] + s0 + w[i - 7] + s1) & 0xFFFFFFFF;
		}
		for(new i = 0; i < 64; i++){
		    s0 = SHA256::RotateRight(a, 2)^SHA256::RotateRight(a, 13)^SHA256::RotateRight(a, 22);
		    new maj = (a&b)^(a&c)^(b&c);
		    new t2 = s0 + maj;
		    s1 = SHA256::RotateRight(e, 6)^SHA256::RotateRight(e, 11)^SHA256::RotateRight(e, 25);
		    new ch = (e&f)^((~e)&g);
		    new t1 = h + s1 + ch + k[i] + w[i];
		    h = g;
		    g = f;
		    f = e;
		    e = (d + t1) & 0xFFFFFFFF;
		    d = c;
		    c = b;
		    b = a;
		    a = (t1 + t2) & 0xFFFFFFFF;
		}

		H[0] = (H[0] + a) & 0xFFFFFFFF;
		H[1] = (H[1] + b) & 0xFFFFFFFF;
		H[2] = (H[2] + c) & 0xFFFFFFFF;
		H[3] = (H[3] + d) & 0xFFFFFFFF;
		H[4] = (H[4] + e) & 0xFFFFFFFF;
		H[5] = (H[5] + f) & 0xFFFFFFFF;
		H[6] = (H[6] + g) & 0xFFFFFFFF;
		H[7] = (H[7] + h) & 0xFFFFFFFF;
	}

	new ret[65];
	new HTemp[8]; HTemp = H;
	new z = sizeof(ret) - 2;
	for(new i = 7; i >= 0; i--){
		new j = 0;
		while(j < 8){
			new mod = HTemp[i]&0xf;
			ret[z--] = (mod<10?(mod+'0'):(mod+'a'-10));
			HTemp[i] >>>= 4;
			j++;
		}
	}
	ret[sizeof(ret) - 1] = '\0';
	
	for(new i = 0, j = strlen(ret); i < j; i++){
		ret[i] = toupper(ret[i]);
	}
	return ret;
}

//SHA256::HashFile by Abyss Morgan for SA:MP
stock SHA256::HashFile(const file_name[],position=0,max_len=cellmax){
	new ret[65];
	if(!fexist(file_name)) return ret;
	new File:inpf = fopen(file_name,io_read);
		
    new H[] =  {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	new k[] =  {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
				0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
				0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
				0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
				0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
				0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
				0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
				0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

 	new it, flen = flength(inpf), length, flen_ex;
	
	fseek(inpf,position,seek_start);
	flen = (flen - position);
	if(flen > max_len) flen = max_len;
	flen_ex = flen * 8;
	length = flen * 8;
	
	length++;
	while((length%512) != 448){
	    length++;
	}
	length += 64;
	it = (length/512);
	
	new buffer[512];
	for(new n = 0; n < it; n++){
	    new sha_256[128*4+1], s0, s1, w[64] = 0;
		
		for(new i = 0; i < 64; i++){
			if(flen > 0){
				buffer[i] = fgetchar(inpf,0,false);
				flen--;
			} else {
				buffer[i] = 0;
			}
		}
		
	 	new len = SHA256::TextToBit(buffer, sha_256, 512);
		if(len < 512){
			sha_256[len++] = '1';

			while((len%512) != 448){
			    sha_256[len++] = '0';
			}
			new tmp[65];
			tmp = SHA256::UINT64ToBit(flen_ex);
			new i = 0;
			while(tmp[i]){
				sha_256[len++] = tmp[i++];
			}
			sha_256[len] = '\0';
		}

  		new a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
		new j = 32;
		for(new x = 0; x < 16; x++){
			w[x] = SHA256::BitToUINT32(sha_256[(j*x)]);
		}
		for(new i = 16; i <= 63; i++){
			s0 = SHA256::RotateRight(w[i - 15], 7)^SHA256::RotateRight(w[i - 15], 18)^(w[i - 15] >>> 3);
			s1 = SHA256::RotateRight(w[i - 2], 17)^SHA256::RotateRight(w[i - 2], 19)^(w[i - 2] >>> 10);
			w[i] = (w[i - 16] + s0 + w[i - 7] + s1) & 0xFFFFFFFF;
		}
		for(new i = 0; i < 64; i++){
		    s0 = SHA256::RotateRight(a, 2)^SHA256::RotateRight(a, 13)^SHA256::RotateRight(a, 22);
		    new maj = (a&b)^(a&c)^(b&c);
		    new t2 = s0 + maj;
		    s1 = SHA256::RotateRight(e, 6)^SHA256::RotateRight(e, 11)^SHA256::RotateRight(e, 25);
		    new ch = (e&f)^((~e)&g);
		    new t1 = h + s1 + ch + k[i] + w[i];
		    h = g;
		    g = f;
		    f = e;
		    e = (d + t1) & 0xFFFFFFFF;
		    d = c;
		    c = b;
		    b = a;
		    a = (t1 + t2) & 0xFFFFFFFF;
		}

		H[0] = (H[0] + a) & 0xFFFFFFFF;
		H[1] = (H[1] + b) & 0xFFFFFFFF;
		H[2] = (H[2] + c) & 0xFFFFFFFF;
		H[3] = (H[3] + d) & 0xFFFFFFFF;
		H[4] = (H[4] + e) & 0xFFFFFFFF;
		H[5] = (H[5] + f) & 0xFFFFFFFF;
		H[6] = (H[6] + g) & 0xFFFFFFFF;
		H[7] = (H[7] + h) & 0xFFFFFFFF;
	}

	fclose(inpf);
	
	new HTemp[8]; HTemp = H;
	new z = sizeof(ret) - 2;
	for(new i = 7; i >= 0; i--){
		new j = 0;
		while(j < 8){
			new mod = HTemp[i]&0xf;
			ret[z--] = (mod<10?(mod+'0'):(mod+'a'-10));
			HTemp[i] >>>= 4;
			j++;
		}
	}
	ret[sizeof(ret) - 1] = '\0';
	
	for(new i = 0, j = strlen(ret); i < j; i++){
		ret[i] = toupper(ret[i]);
	}
	return ret;
}

//EOF