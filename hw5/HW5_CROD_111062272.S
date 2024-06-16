# Reference: https://www.geeksforgeeks.org/c-program-for-cutting-a-rod-dp-13/?ref=header_search

.data
.align 4

# =========testcase1===========
# arr: .word 8, 13, 5, 9
# length: .word 4
# str: .string "output: "
# space: .string " "
# output: 32
# ==============================

# =========testcase2===========
# (run about 4 min)
arr: .word 3, 6, 12, 5, 10
length: .word 5
str: .string "output: "
space: .string " "
# output: 18
# ==============================

.text
.global _start #0x11970

# Start your coding below, don't change anything upper except testing different testcase
_start:
    lw a1, length
    la t3, arr # const: base addr of arr
    jal ra, cut

    # print "output: "
    la a0, str
    li a7, 4
    ecall

    # print max_val
    mv a0, a2
    li a7, 1
    ecall

    # end program
    li a7, 10
    ecall

# func
cut: # n @ a1 => max_val @ a2
    bge a1, x0, gtzero
    li a2, 0
    jr ra

gtzero:
    # sp[0]: ra
    # sp[4]: n
    # sp[8] / t0: max_val
    # sp[12] / t1: i

    addi sp, sp, -16
    sw ra, 0(sp)
    sw a1, 4(sp) # n

    li t0, 0 # max_val
    li t1, 0 # i
    jal ra, doSS

loop:
    lw a0, 4(sp)
    bge t1, a0, loop_end
    
    # n - i - 1
    sub a1, a0, t1
    addi a1, a1, -1

    jal ra, doSS
    jal ra, cut # cut(n - i - 1)
    jal ra, loadSS

    # arr[i] -> t4
    mv t4, t1
    slli t4, t4, 2
    add t4, t4, t3
    lw t4, 0(t4)

    add a2, a2, t4
    ble a2, t0, skip_update_max
    mv t0, a2

skip_update_max:
    addi t1, t1, 1
    j loop

loop_end:
    lw ra, 0(sp)
    addi sp, sp, 16
    
    mv a2, t0
    jr ra

doSS: # do snapshot
    sw t0, 8(sp)
    sw t1, 12(sp)
    
    jr ra

loadSS: # load snapshot
    lw t0, 8(sp)
    lw t1, 12(sp)

    jr ra