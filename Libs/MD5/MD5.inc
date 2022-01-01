/****************************************************************************************************
 *                                                                                                  *
 *                                          )(   MD5   )(                                           *
 *                                                                                                  *
 * Copyright © 2022 Ron Rivest. All rights reserved.                                                *
 * Contributors: Colin Plumb, Y_Less, Abyss Morgan                                                  *
 *                                                                                                  *
 * Website: https://adm.ct8.pl                                                                      *
 *                                                                                                  *
 * Plugins: None                                                                                    *
 * Modules: None                                                                                    *
 *                                                                                                  *
 * File Version: 1.0.0                                                                              *
 *                                                                                                  *
 * Functions:                                                                                       *
 * MD5::Hash(str[]);                                                                                *
 * MD5::HashFile(const file_name[],position=0,max_len=cellmax);                                     *
 *                                                                                                  *
 ****************************************************************************************************/

#if defined _MD5_HASH
	#endinput
#endif
#define _MD5_HASH

#define MD5::							MD5_

enum MD5::Enum {
	MD5::CONTEXT_BUF[4],
	MD5::CONTEXT_BITS[2],
	MD5::CONTEXT_IN[64 char]
}

#define MD5_F1(%1,%2,%3)				(%3 ^ (%1 & (%2 ^ %3)))
#define MD5_F2(%1,%2,%3)				MD5_F1(%3, %1, %2)
#define MD5_F3(%1,%2,%3)				(%1 ^ %2 ^ %3)
#define MD5_F4(%1,%2,%3)				(%2 ^ (%1 | ~%3))

#define MD5_Step(%1,%2,%3,%4,%5,%6,%7)	%2 += %1(%3, %4, %5) + %6, %2 = %2 << %7 | %2 >>> (32 - %7), %2 += %3

stock MD5::Hash(str[]){
	new md5Data[MD5::Enum], done, digest[34], len = strlen(str);
	MD5::Init(md5Data);
	len -= 64;
	while(done < len){
		MD5::Update(md5Data,str[done],64);
		done += 64;
	}
	len = (len + 64) - done;
	if(len){
		MD5::Update(md5Data,str[done],len);
	}
	digest = MD5::Final(md5Data,true);
	return digest;
}

//MD5::HashFile by Abyss Morgan for SA:MP
stock MD5::HashFile(const file_name[],position=0,max_len=cellmax){
	new digest[34];
	if(!fexist(file_name)) return digest;
	new File:inpf = fopen(file_name,io_read),
		md5Data[MD5::Enum],
		done = 0,
		buffer[64],
		len = flength(inpf);
	
	fseek(inpf,position,seek_start);
	len = (len - position);
	if(len > max_len) len = max_len;
	
	MD5::Init(md5Data);
	len -= 64;
	while(done < len){
		for(new i = 0; i < 64; i++){
			buffer[i] = fgetchar(inpf,0,false);
		}
		MD5::Update(md5Data,buffer,64);
		done += 64;
	}
	len = (len + 64) - done;
	if(len){
		for(new i = 0; i < len; i++){
			buffer[i] = fgetchar(inpf,0,false);
		}
		MD5::Update(md5Data,buffer,len);
	}
	fclose(inpf);
	digest = MD5::Final(md5Data,true);
	return digest;
}

stock MD5::Init(ctx[MD5::Enum]){
	ctx[MD5::CONTEXT_BUF][0] = 0x67452301;
	ctx[MD5::CONTEXT_BUF][1] = 0xEFCDAB89;
	ctx[MD5::CONTEXT_BUF][2] = 0x98BADCFE;
	ctx[MD5::CONTEXT_BUF][3] = 0x10325476;
	ctx[MD5::CONTEXT_BITS][0] = 0;
	ctx[MD5::CONTEXT_BITS][1] = 0;
}

stock MD5::Update(ctx[MD5::Enum], const data[], len){
	new t = ctx[MD5::CONTEXT_BITS][0], s, buf = 0;
	if((ctx[MD5::CONTEXT_BITS][0] = t + (len << 3)) < t){
		ctx[MD5::CONTEXT_BITS][1]++;
	}
	ctx[MD5::CONTEXT_BITS][1] += len >>> 29;
	t = (t >>> 3) & 0x3F;
	if(t){
		s = 64 - t;
		if(len < s){
			MD5::copy(ctx[MD5::CONTEXT_IN], data, t, len);
			return;
		}
		MD5::copy(ctx[MD5::CONTEXT_IN], data, t, s);
		MD5::Transform(ctx[MD5::CONTEXT_BUF], ctx[MD5::CONTEXT_IN]);
		buf += s;
		len -= s;
	}
	while(len >= 64){
		MD5::copy(ctx[MD5::CONTEXT_IN], data[buf], 0, 64);
		MD5::Transform(ctx[MD5::CONTEXT_BUF], ctx[MD5::CONTEXT_IN]);
		buf += 64;
		len -= 64;
	}
	MD5::copy(ctx[MD5::CONTEXT_IN], data[buf], 0, len);
}

stock MD5::copy(dest[],const src[],start,len){
	new i = start >>> 2, j = 0, ch;
	while(j < len){
		ch = src[j++] & 0xFF;
		switch(start++ & 0x03){
			case 0: dest[i] = ch;
			case 1: dest[i] |= ch << 8;
			case 2: dest[i] |= ch << 16;
			case 3: dest[i++] |= ch << 24;
		}
	}
}

stock MD5::Final(ctx[MD5::Enum], string = false){
	new count, index, digest[33];
	count = (ctx[MD5::CONTEXT_BITS][0] >>> 3) & 0x3F;
	if(!(count & 0x03)){
		ctx[MD5::CONTEXT_IN][count / 4] = 0;
	}
	ctx[MD5::CONTEXT_IN][count / 4] |= (0x80 << (8 * (count & 0x03)));
	index = (count / 4) + 1;
	count = 64 - 1 - count;
	if(count < 8){
		while(index < 64 char){
			ctx[MD5::CONTEXT_IN][index++] = 0;
		}
		MD5::Transform(ctx[MD5::CONTEXT_BUF], ctx[MD5::CONTEXT_IN]);
		index = 0;
		while(index < 56 char){
			ctx[MD5::CONTEXT_IN][index++] = 0;
		}
	} else {
		while(index < 56 char){
			ctx[MD5::CONTEXT_IN][index++] = 0;
		}
	}
	ctx[MD5::CONTEXT_IN][14] = ctx[MD5::CONTEXT_BITS][0];
	ctx[MD5::CONTEXT_IN][15] = ctx[MD5::CONTEXT_BITS][1];
	MD5::Transform(ctx[MD5::CONTEXT_BUF], ctx[MD5::CONTEXT_IN]);
	if(string){
		index = 0;
		do {
			format(digest, sizeof (digest), "%s%02x", digest, (ctx[MD5::CONTEXT_BUF][index / 4] >> ((index & 0x03) * 8)) & 0xFF);
		}
		while(++index < 16);
	}
	return digest;
}

static stock MD5::Transform(buf[],const in[]){
	new a = buf[0], b = buf[1], c = buf[2], d = buf[3];
	MD5::Step(MD5::F1,a,b,c,d,in[0]+0xD76AA478,7);
	MD5::Step(MD5::F1,d,a,b,c,in[1]+0xE8C7B756,12);
	MD5::Step(MD5::F1,c,d,a,b,in[2]+0x242070DB,17);
	MD5::Step(MD5::F1,b,c,d,a,in[3]+0xC1BDCEEE,22);
	MD5::Step(MD5::F1,a,b,c,d,in[4]+0xF57C0FAF,7);
	MD5::Step(MD5::F1,d,a,b,c,in[5]+0x4787C62A,12);
	MD5::Step(MD5::F1,c,d,a,b,in[6]+0xA8304613,17);
	MD5::Step(MD5::F1,b,c,d,a,in[7]+0xFD469501,22);
	MD5::Step(MD5::F1,a,b,c,d,in[8]+0x698098D8,7);
	MD5::Step(MD5::F1,d,a,b,c,in[9]+0x8B44F7AF,12);
	MD5::Step(MD5::F1,c,d,a,b,in[10]+0xFFFF5BB1,17);
	MD5::Step(MD5::F1,b,c,d,a,in[11]+0x895CD7BE,22);
	MD5::Step(MD5::F1,a,b,c,d,in[12]+0x6B901122,7);
	MD5::Step(MD5::F1,d,a,b,c,in[13]+0xFD987193,12);
	MD5::Step(MD5::F1,c,d,a,b,in[14]+0xA679438E,17);
	MD5::Step(MD5::F1,b,c,d,a,in[15]+0x49B40821,22);
	MD5::Step(MD5::F2,a,b,c,d,in[1]+0xF61E2562,5);
	MD5::Step(MD5::F2,d,a,b,c,in[6]+0xC040B340,9);
	MD5::Step(MD5::F2,c,d,a,b,in[11]+0x265E5A51,14);
	MD5::Step(MD5::F2,b,c,d,a,in[0]+0xE9B6C7AA,20);
	MD5::Step(MD5::F2,a,b,c,d,in[5]+0xD62F105D,5);
	MD5::Step(MD5::F2,d,a,b,c,in[10]+0x02441453,9);
	MD5::Step(MD5::F2,c,d,a,b,in[15]+0xD8A1E681,14);
	MD5::Step(MD5::F2,b,c,d,a,in[4]+0xE7D3FBC8,20);
	MD5::Step(MD5::F2,a,b,c,d,in[9]+0x21E1CDE6,5);
	MD5::Step(MD5::F2,d,a,b,c,in[14]+0xC33707D6,9);
	MD5::Step(MD5::F2,c,d,a,b,in[3]+0xF4D50D87,14);
	MD5::Step(MD5::F2,b,c,d,a,in[8]+0x455A14ED,20);
	MD5::Step(MD5::F2,a,b,c,d,in[13]+0xA9E3E905,5);
	MD5::Step(MD5::F2,d,a,b,c,in[2]+0xFCEFA3F8,9);
	MD5::Step(MD5::F2,c,d,a,b,in[7]+0x676F02D9,14);
	MD5::Step(MD5::F2,b,c,d,a,in[12]+0x8D2A4C8A,20);
	MD5::Step(MD5::F3,a,b,c,d,in[5]+0xFFFA3942,4);
	MD5::Step(MD5::F3,d,a,b,c,in[8]+0x8771F681,11);
	MD5::Step(MD5::F3,c,d,a,b,in[11]+0x6D9D6122,16);
	MD5::Step(MD5::F3,b,c,d,a,in[14]+0xFDE5380C,23);
	MD5::Step(MD5::F3,a,b,c,d,in[1]+0xA4BEEA44,4);
	MD5::Step(MD5::F3,d,a,b,c,in[4]+0x4BDECFA9,11);
	MD5::Step(MD5::F3,c,d,a,b,in[7]+0xF6BB4B60,16);
	MD5::Step(MD5::F3,b,c,d,a,in[10]+0xBEBFBC70,23);
	MD5::Step(MD5::F3,a,b,c,d,in[13]+0x289B7EC6,4);
	MD5::Step(MD5::F3,d,a,b,c,in[0]+0xEAA127FA,11);
	MD5::Step(MD5::F3,c,d,a,b,in[3]+0xD4EF3085,16);
	MD5::Step(MD5::F3,b,c,d,a,in[6]+0x04881D05,23);
	MD5::Step(MD5::F3,a,b,c,d,in[9]+0xD9D4D039,4);
	MD5::Step(MD5::F3,d,a,b,c,in[12]+0xE6DB99E5,11);
	MD5::Step(MD5::F3,c,d,a,b,in[15]+0x1FA27CF8,16);
	MD5::Step(MD5::F3,b,c,d,a,in[2]+0xC4AC5665,23);
	MD5::Step(MD5::F4,a,b,c,d,in[0]+0xF4292244,6);
	MD5::Step(MD5::F4,d,a,b,c,in[7]+0x432AFF97,10);
	MD5::Step(MD5::F4,c,d,a,b,in[14]+0xAB9423A7,15);
	MD5::Step(MD5::F4,b,c,d,a,in[5]+0xFC93A039,21);
	MD5::Step(MD5::F4,a,b,c,d,in[12]+0x655B59C3,6);
	MD5::Step(MD5::F4,d,a,b,c,in[3]+0x8F0CCC92,10);
	MD5::Step(MD5::F4,c,d,a,b,in[10]+0xFFEFF47D,15);
	MD5::Step(MD5::F4,b,c,d,a,in[1]+0x85845DD1,21);
	MD5::Step(MD5::F4,a,b,c,d,in[8]+0x6FA87E4F,6);
	MD5::Step(MD5::F4,d,a,b,c,in[15]+0xFE2CE6E0,10);
	MD5::Step(MD5::F4,c,d,a,b,in[6]+0xA3014314,15);
	MD5::Step(MD5::F4,b,c,d,a,in[13]+0x4E0811A1,21);
	MD5::Step(MD5::F4,a,b,c,d,in[4]+0xF7537E82,6);
	MD5::Step(MD5::F4,d,a,b,c,in[11]+0xBD3AF235,10);
	MD5::Step(MD5::F4,c,d,a,b,in[2]+0x2AD7D2BB,15);
	MD5::Step(MD5::F4,b,c,d,a,in[9]+0xEB86D391,21);
	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;
}

//EOF