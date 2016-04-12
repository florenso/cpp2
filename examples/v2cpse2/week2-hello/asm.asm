.text

.global print_asciz
print_asciz:
   push { r5, lr }
   mov  r5, r0
loop: 
   ldrb r0, [ r5 ]
   add  r0, r0, #0
   beq  done
   bl   magic
   bl   put_char
   add  r5, r5, #1
   b    loop
done: 
   pop  { r5, pc }
   
.global application
application:
push {lr}
ldr r0, =string
bl print_asciz
pop {pc}

string: .asciz "Hello world, the ANSWER is 42!\n"

magic:
push {lr}
cmp r0,#'a'-1
ble  magic_not_lower
cmp r0,#'z'+1
bge magic_not_lower
sub r0,r0,#32
pop {pc}
magic_not_lower:
cmp r0,#'A'-1
ble magic_not_upper
cmp r0,#'Z'+1
bge magic_not_upper
add r0,r0,#32
magic_not_upper:
pop {pc}

