/*********** ts.s file of Program C2.3 **********/
        .global start, sum
start:  ldr sp, =stack_top
        bl main // call main() in C
stop:   b stop

sum: // int sum(int a,b,c,d,e,f){ return a+b+e+d+e+f;}
// upon entry, stack top contains e, f, passed by main()in C
// Establish stack frame
        stmfd sp!, {fp, lr} // push fp, lr
        add fp, sp, #4 // fp -> saved lr on stack
// Compute sum of all (6) parameters
        add r0, r0, r1 // first 4 parameters are in r0-r3
        add r0, r0, r2
        add r0, r0, r3
        ldr r3, [fp, #4] // load e into r3
        add r0, r0, r3 // add to sum in r0
        ldr r3, [fp, #8] // load f into r3
        add r0, r0, r3 // add to sum in r0
// Return to caller
        sub sp, fp, #4 // sp=fp-4 (point at saved FP)
        ldmfd sp!, {fp, pc} // return to caller
        