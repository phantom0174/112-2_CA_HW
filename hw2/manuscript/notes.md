# notes

## 1 d

sum of a: 6+7+6 = 19
sum of b: 6+7+6 = 19
sum of c: 6+1+8+1+5+7+1 = 29

ori: 19+19+29 = 67
now: 19+29 = 48

=> speedup = 67/48 ~ 1.3958 < 2



## 2 
(a)

| Instruction ID | Hexadecimal Encoded instruction | Decoded Instruction |
|----------------|---------------------------------|---------------------|
| 5 | 0x0040 8067 | jalr x0, 4(x1) |
| 6 | 0xFF84 3283 | ld x5, -8(x8) |
| 8 | 0x4142 D293 | srai x5, x5, 20 |

ID 5: jump directly to memory x1 + 4, don't save return addresss
ID 6: load M[x8 - 8] to reg x5
ID 8: shift reg x5 right for (20/4) = 5 hex units

(b)
| Instruction ID | Updated register | Updated memory |
|----------------|------------------|----------------|
| 1 | x7 = x5 - x6 = 0x0004 | - |
| 2 | - | M[0000 003E FF20 13F0] = 0xFF20 13E0<br>M[0000 003E FF20 13F4] = 0x0000 003E |
| 3 | x1 = PC + 4 = 0x0000 0000 0001 00BC | - |
| 6 | x5 = M[0x0000 003E FF20 13F8] = 0x0041 0000 | - |
| 7 | x5 = x30 & x5 = 0x0040 0000 | - |
| 8 | x5 >>= 4 = 0x0004 | - |
| 9 | - | - |
| 10 | x28 = x2 = 0x0000 003E FF20 13E0 | - |
| 11 | x7 <-(byte) M[0x0000 003E FF20 13EA] = 0xFFFF FFFF FFFF FF91 | - |
| 12 | - | - |
| 13 | x1 = PC + 4 = 0x0000 0000 0001 00E4 | - |
| 4 | x5 <-(word) M[0x0000 003E FF20 13E4] = 0x3F10 | - |
| 5 | - | - |
| 15 | x7 = x6 ^ x7 = 0xFFFF FFFF FFFF C081 | - |
| 16 | x7 >>= 4 = 0xFFFF FFFF FFFF FFFF | - |
| 17 | x31 = x6 + 1000 = 0x3F1A | - |
| 18 | x31 >>= 4 = 0x0 | - |
| 19 | - | M[0x0000 003E FF20 13F8] = 0x0041 0004 |
| 20 | - | M[0x0000 003E FF20 13E8] = 0x0<br> M[0x0000 003E FF20 13EA] = 0x00F0 |

(c)
Count of total operations: 18

(d)

offset = -15 * 4 = -60
using half word address => -30
-30 = 1...10 0010

| imm[12  \ | 10:5] | rs2 | rs1 | funct3 | imm[4:1  \ | 11] | opcode |
|-----------|-------|-----|-----|--------|------------|-----|--------|
| 1 11110 | 00111 | 11111 | 100 | 0010 1 | 1100011 | - | - |

hex: 0xFC7FC2E3

since x31 = 0x0, x7 = 0xFFFF FFFF FFFF FFFF
=> x31 > x7

dont branch

| Code address | Assembly instruction | Hexadecimal encoded instruction | Taken? |
|--------------|----------------------|---------------------------------|--------|
| 0x0000 0000 0001 0100 | blt x31, x7, -60 | 0xFC7FC2E3 | No |

## 3


===========================

i = 0;
a = &A[0];

while (i < m) {
    j = 0;
    total = 0;
    b = *a;

    c = 32;
    while (j < c) {
		d = b >> j;
		d %= 2;
		total += d;
		j++;
    }

	*a = total;
	a++;
	i++;
}

===========================

int* a = &A[0];
for (int i = 0; i < m; i++, a++) {
	total = 0;
	b = *a;

	const c = 32;
	for (int j = 0; j < c; j++) {
		total += (b >> j) % 2;
	}
	*a = total;
}

===========================

// bits counter for A array for element 0th ~ (m-1)th

int* a = &A[0];
for (int i = 0; i < m; i++, a++) {
	int total = 0, b = *a;

	for (int j = 0; j < 32; j++) { // count 1s in b
		total += (b >> j) % 2;
	}
	*a = total;
}

===========================

// bits counter for MemArray[0] ~ MemArray[m - 1]

int* a = &MemArray[0];
for (int i = 0; i < m; i++, a++) {
	int total = 0, b = *a;

	// count 1s in b's binary format
	for (int j = 0; j < 32; j++) {
		total += (b >> j) % 2;
	}
	*a = total;
}

## 4

j = *(&B + *(&A + 4i + 1)) + *(&B + i)

(a)

```text
num1:
	slli t0, x7, 2
	addi t0, t0, 1
	slli t0, t0, 2
	add t0, t0, x5
	lw t0, 0(t0)
	slli t0, t0, 2
	add t0, t0, x6
	lw t0, 0(t0)
num2:
	slli t1, x7, 2
	add t1, t1, x6
	lw t1, 0(t1)
sum:
	add x11, t0, t1
```

(b)

```text
num1:
	slli t0, x7, 2
	addi t0, t0, 1
	slli t0, t0, 3
	add t0, t0, x5
	ld t0, 0(t0)
	slli t0, t0, 3
	add t0, t0, x6
	ld t0, 0(t0)
num2:
	slli t1, x7, 3
	add t1, t1, x6
	ld t1, 0(t1)
sum:
	add x11, t0, t1
```

## 5

fact:
	addi sp,sp,-16 # make space on stack
	sd ra,8(sp) # save return address in x1 onto stack
	sd a0,0(sp) # save argument in x10 onto stack
	addi t0,a0,-1 # t0 = n – 1
	bge t0,zero,L1 # if (n - 1) >= 0, go to L1
	addi a0,zero,1 # else, set return value to 1
	addi sp,sp,16 # pop stack, don’t bother restoring values
	jalr zero,0(ra) # return
L1:
	addi a0,a0,-1 # n = n – 1
	jal ra,fact # call fact(n – 1)
	addi t1,a0,0 # move return value of fact(n – 1) to t1
	ld a0,0(sp) # restore caller’s n
	ld ra,8(sp) # restore return address
	addi sp,sp,16 # return space on stack
	mul a0,a0,t1 # return n * fact(n – 1)
	jalr zero,0(ra) # return


long long int Func(int n);
- used
	n: a0
	ra, zero


func:
	addi sp, sp, -16 # save caller's args & return address
	sd ra, 0(sp)
	sd a0, 8(sp)

	bne a0, zero, NOT_ZERO
	addi a0, zero, 0 # set return to 0
	addi sp, sp, 16 # restore stack for caller
	jalr x0, 0(ra) # return

NOT_ZERO:
	andi t0, a0, 1 # check n's parity, save result in t0
	bne t0, zero, IS_ODD

	srai a0, a0, 1 # ready to call Func(n >> 1)
	jal ra, func
	mv t1, a0 # save return value in t1

	ld ra, 0(sp) # restore stack
	ld a0, 8(sp)
	addi sp, sp, 16

	add a0, a0, t1 # set return value to n + t1
	jalr zero, 0(ra) # return

IS_ODD:
	srai a0, a0, 1 # ready to call Func(n >> 1)
	jal ra, func
	mv t1, a0 # save return value in t1

	ld ra, 0(sp) # restore stack
	ld a0, 8(sp)
	addi sp, sp, 16

	add a0, t1, 0 # set return value to t1
	jalr zero, 0(ra) # return
