1.

a:
sd, ld: need simm12
beq (since a is connected to shift left in pc)

b:

connected to `write data` => not sd

ans: add, beq

c:

sd: rs2, simm12(rs1)

branch: is possible that pc will be modified if (simm2 + rs1 == 0)
memRead: don't care (0)
memToReg: don't care (0)
memWrite: 1
aluSrc: 1
regWrite: 0, or will store wrong data in reg

6.

b:

| Ground truth | NT  |  T  |  T  | NT  | NT  | NT  | NT  |  T  |
| :----------: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|    State     |  T  | NT  |  T  |  T  | NT  | NT  | NT  | NT  |
|   Decision   |  T  | NT  |  T  |  T  | NT  | NT  | NT  | NT  |
| Correctness  |  F  |  F  |  T  |  F  |  T  |  T  |  T  |  F  |

accuracy: 4/8

c:

| Ground truth | NT  |  T  |  T  | NT  | NT  | NT  | NT  |  T  |
| :----------: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|    State     | sT  | wT  | sT  | sT  | wT  | wNT | sNT | sNT |
|   Decision   |  T  |  T  |  T  |  T  |  T  | NT  | NT  | NT  |
| Correctness  |  F  |  T  |  T  |  F  |  F  |  T  |  T  |  F  |

accuracy: 4/8

8.

|     | IF  | ID      | EX  | MEM | WB  |
| --- | --- | ------- | --- | --- | --- |
| C1  | add | -       | -   | -   | -   |
| C2  | sub | add     | -   | -   | -   |
| C3  | beq | sub     | add | -   | -   |
| C4  | sd  | **beq** | sub | add | -   |
| C5  | EH  | NOP     | NOP | sub | add |
