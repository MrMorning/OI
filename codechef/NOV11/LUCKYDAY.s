	.file	"LUCKYDAY_cp.cpp"
	.section	.text._ZSt19__move_median_firstIP5QueryEvT_S2_S2_,"axG",@progbits,_ZSt19__move_median_firstIP5QueryEvT_S2_S2_,comdat
	.p2align 4,,15
	.weak	_ZSt19__move_median_firstIP5QueryEvT_S2_S2_
	.type	_ZSt19__move_median_firstIP5QueryEvT_S2_S2_, @function
_ZSt19__move_median_firstIP5QueryEvT_S2_S2_:
.LFB441:
	.cfi_startproc
	subl	$36, %esp
	.cfi_def_cfa_offset 40
	movl	44(%esp), %edx
	movl	40(%esp), %eax
	movl	%esi, 24(%esp)
	movl	48(%esp), %ecx
	movl	%ebx, 20(%esp)
	movl	8(%edx), %esi
	.cfi_offset 3, -20
	.cfi_offset 6, -16
	movl	12(%eax), %ebx
	movl	%edi, 28(%esp)
	movl	8(%eax), %edi
	.cfi_offset 7, -12
	movl	%ebp, 32(%esp)
	movl	%esi, 4(%esp)
	movl	12(%edx), %esi
	cmpl	%esi, %ebx
	jg	.L2
	.cfi_offset 5, -8
	jge	.L17
.L11:
	movl	8(%ecx), %ebp
	movl	%ebp, 12(%esp)
	movl	12(%ecx), %ebp
	cmpl	%ebp, %esi
	movl	%ebp, 8(%esp)
	jle	.L18
.L4:
	cmpl	8(%esp), %ebx
	jg	.L1
	jl	.L15
	cmpl	12(%esp), %edi
	.p2align 4,,3
	jb	.L15
	.p2align 4,,7
	.p2align 3
.L1:
	movl	20(%esp), %ebx
	movl	24(%esp), %esi
	movl	28(%esp), %edi
	movl	32(%esp), %ebp
	addl	$36, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	.cfi_restore 7
	.cfi_restore 6
	.cfi_restore 3
	ret
	.p2align 4,,7
	.p2align 3
.L17:
	.cfi_restore_state
	cmpl	4(%esp), %edi
	jb	.L11
.L2:
	movl	8(%ecx), %ebp
	movl	%ebp, 12(%esp)
	movl	12(%ecx), %ebp
	cmpl	%ebp, %ebx
	movl	%ebp, 8(%esp)
	jl	.L1
	jle	.L19
.L14:
	cmpl	8(%esp), %esi
	jg	.L9
	.p2align 4,,7
	jl	.L15
	movl	12(%esp), %esi
	cmpl	%esi, 4(%esp)
	jb	.L15
	.p2align 4,,7
	.p2align 3
.L9:
	movl	(%edx), %ebp
	movl	(%eax), %esi
	movl	4(%eax), %ecx
	movl	%ebp, (%eax)
	movl	4(%edx), %ebp
	movl	%ebp, 4(%eax)
	movl	8(%edx), %ebp
	movl	%ebp, 8(%eax)
	movl	12(%edx), %ebp
	movl	%ebp, 12(%eax)
	movl	%esi, (%edx)
	movl	%ecx, 4(%edx)
	movl	%edi, 8(%edx)
	movl	%ebx, 12(%edx)
	jmp	.L1
	.p2align 4,,7
	.p2align 3
.L18:
	jl	.L9
	movl	12(%esp), %esi
	cmpl	%esi, 4(%esp)
	jae	.L4
	.p2align 4,,3
	jmp	.L9
	.p2align 4,,7
	.p2align 3
.L19:
	cmpl	12(%esp), %edi
	jb	.L1
	.p2align 4,,7
	jmp	.L14
	.p2align 4,,7
	.p2align 3
.L15:
	movl	(%ecx), %ebp
	movl	(%eax), %esi
	movl	4(%eax), %edx
	movl	%ebp, (%eax)
	movl	4(%ecx), %ebp
	movl	%ebp, 4(%eax)
	movl	8(%ecx), %ebp
	movl	%ebp, 8(%eax)
	movl	12(%ecx), %ebp
	movl	%ebp, 12(%eax)
	movl	%esi, (%ecx)
	movl	%edx, 4(%ecx)
	movl	%edi, 8(%ecx)
	movl	%ebx, 12(%ecx)
	jmp	.L1
	.cfi_endproc
.LFE441:
	.size	_ZSt19__move_median_firstIP5QueryEvT_S2_S2_, .-_ZSt19__move_median_firstIP5QueryEvT_S2_S2_
	.section	.text._ZSt25__unguarded_linear_insertIP5QueryEvT_,"axG",@progbits,_ZSt25__unguarded_linear_insertIP5QueryEvT_,comdat
	.p2align 4,,15
	.weak	_ZSt25__unguarded_linear_insertIP5QueryEvT_
	.type	_ZSt25__unguarded_linear_insertIP5QueryEvT_, @function
_ZSt25__unguarded_linear_insertIP5QueryEvT_:
.LFB444:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	movl	20(%esp), %edx
	movl	12(%edx), %ebx
	cmpl	-4(%edx), %ebx
	movl	(%edx), %ebp
	movl	4(%edx), %edi
	movl	8(%edx), %esi
	jg	.L21
	jge	.L29
.L26:
	leal	-16(%edx), %eax
	.p2align 4,,7
	.p2align 3
.L23:
	movl	(%eax), %ecx
	movl	%ecx, (%edx)
	movl	4(%eax), %ecx
	movl	%ecx, 4(%edx)
	movl	8(%eax), %ecx
	movl	%ecx, 8(%edx)
	movl	12(%eax), %ecx
	movl	%ecx, 12(%edx)
	leal	-16(%eax), %ecx
	cmpl	%ebx, 12(%ecx)
	jg	.L25
	jge	.L30
.L27:
	movl	%eax, %edx
.L21:
	movl	%ebp, (%edx)
	movl	%edi, 4(%edx)
	movl	%esi, 8(%edx)
	movl	%ebx, 12(%edx)
	popl	%ebx
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
	.p2align 4,,7
	.p2align 3
.L30:
	.cfi_restore_state
	cmpl	%esi, 8(%ecx)
	jbe	.L27
.L25:
	movl	%eax, %edx
	movl	%ecx, %eax
	jmp	.L23
	.p2align 4,,7
	.p2align 3
.L29:
	cmpl	-8(%edx), %esi
	jb	.L26
	movl	%ebp, (%edx)
	movl	%edi, 4(%edx)
	movl	%esi, 8(%edx)
	movl	%ebx, 12(%edx)
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE444:
	.size	_ZSt25__unguarded_linear_insertIP5QueryEvT_, .-_ZSt25__unguarded_linear_insertIP5QueryEvT_
	.section	.text._ZSt16__insertion_sortIP5QueryEvT_S2_,"axG",@progbits,_ZSt16__insertion_sortIP5QueryEvT_S2_,comdat
	.p2align 4,,15
	.weak	_ZSt16__insertion_sortIP5QueryEvT_S2_
	.type	_ZSt16__insertion_sortIP5QueryEvT_S2_, @function
_ZSt16__insertion_sortIP5QueryEvT_S2_:
.LFB437:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$60, %esp
	.cfi_def_cfa_offset 80
	movl	80(%esp), %esi
	cmpl	84(%esp), %esi
	je	.L31
	leal	16(%esi), %ebx
	cmpl	%ebx, 84(%esp)
	je	.L31
	leal	32(%esi), %edi
	jmp	.L37
	.p2align 4,,7
	.p2align 3
.L33:
	movl	%ebx, (%esp)
	addl	$16, %ebx
	call	_ZSt25__unguarded_linear_insertIP5QueryEvT_
	movl	%edi, %ecx
	addl	$16, %edi
	cmpl	84(%esp), %ecx
	je	.L31
.L37:
	movl	12(%ebx), %ebp
	cmpl	12(%esi), %ebp
	movl	8(%ebx), %edx
	jg	.L33
	jl	.L38
	cmpl	8(%esi), %edx
	jae	.L33
.L38:
	movl	(%ebx), %eax
	movl	%edi, %ecx
	movl	%eax, 40(%esp)
	movl	4(%ebx), %eax
	movl	%eax, 44(%esp)
	movl	%ebx, %eax
	subl	%esi, %eax
	sarl	$4, %eax
	testl	%eax, %eax
	jne	.L40
.L35:
	movl	40(%esp), %eax
	addl	$16, %edi
	addl	$16, %ebx
	cmpl	84(%esp), %ecx
	movl	%edx, 8(%esi)
	movl	%ebp, 12(%esi)
	movl	%eax, (%esi)
	movl	44(%esp), %eax
	movl	%eax, 4(%esi)
	jne	.L37
.L31:
	addl	$60, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
	.p2align 4,,7
	.p2align 3
.L40:
	.cfi_restore_state
	sall	$4, %eax
	movl	%eax, 28(%esp)
	movl	%eax, 8(%esp)
	movl	%edi, %eax
	subl	28(%esp), %eax
	movl	%edx, 32(%esp)
	movl	%esi, 4(%esp)
	movl	%eax, (%esp)
	movl	%edi, 36(%esp)
	call	memmove
	movl	36(%esp), %ecx
	movl	32(%esp), %edx
	jmp	.L35
	.cfi_endproc
.LFE437:
	.size	_ZSt16__insertion_sortIP5QueryEvT_S2_, .-_ZSt16__insertion_sortIP5QueryEvT_S2_
	.section	.text._ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_,"axG",@progbits,_ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_,comdat
	.p2align 4,,15
	.weak	_ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_
	.type	_ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_, @function
_ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_:
.LFB455:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	movl	24(%esp), %ebp
	cmpl	28(%esp), %ebp
	movl	20(%esp), %ebx
	movl	40(%esp), %edi
	movl	44(%esp), %esi
	jle	.L50
	leal	-1(%ebp), %eax
	movl	%eax, %ecx
	shrl	$31, %ecx
	addl	%eax, %ecx
	sarl	%ecx
	movl	%ecx, %eax
	sall	$4, %eax
	addl	%ebx, %eax
	cmpl	12(%eax), %esi
	jle	.L56
	.p2align 4,,7
	.p2align 3
.L51:
	movl	%ecx, %edx
	movl	%ebp, %eax
	sall	$4, %edx
	addl	%ebx, %edx
	movl	(%edx), %ebp
	sall	$4, %eax
	addl	%ebx, %eax
	cmpl	%ecx, 28(%esp)
	movl	%ebp, (%eax)
	movl	4(%edx), %ebp
	movl	%ebp, 4(%eax)
	movl	8(%edx), %ebp
	movl	%ebp, 8(%eax)
	movl	12(%edx), %ebp
	movl	%ebp, 12(%eax)
	jl	.L48
.L43:
	movl	32(%esp), %eax
	movl	%edi, 8(%edx)
	movl	%esi, 12(%edx)
	movl	%eax, (%edx)
	movl	36(%esp), %eax
	movl	%eax, 4(%edx)
	popl	%ebx
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
	.p2align 4,,7
	.p2align 3
.L48:
	.cfi_restore_state
	leal	-1(%ecx), %eax
	movl	%eax, %ebp
	shrl	$31, %ebp
	addl	%ebp, %eax
	sarl	%eax
	movl	%eax, %ebp
	sall	$4, %ebp
	addl	%ebx, %ebp
	cmpl	%esi, 12(%ebp)
	jl	.L49
	jg	.L43
	cmpl	%edi, 8(%ebp)
	jae	.L43
.L49:
	movl	%ecx, %ebp
	movl	%eax, %ecx
	.p2align 4,,4
	jmp	.L51
	.p2align 4,,7
	.p2align 3
.L56:
	jl	.L50
	cmpl	8(%eax), %edi
	.p2align 4,,4
	ja	.L51
	.p2align 4,,7
	.p2align 3
.L50:
	movl	%ebp, %edx
	sall	$4, %edx
	addl	%ebx, %edx
	jmp	.L43
	.cfi_endproc
.LFE455:
	.size	_ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_, .-_ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_
	.section	.text._ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_,"axG",@progbits,_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_,comdat
	.p2align 4,,15
	.weak	_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_
	.type	_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_, @function
_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_:
.LFB450:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	movl	52(%esp), %eax
	movl	56(%esp), %ebp
	movl	48(%esp), %ecx
	movl	%eax, 8(%esp)
	movl	%ebp, %eax
	subl	$1, %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%eax, %edx
	movl	%edx, 4(%esp)
	movl	8(%esp), %edx
	sarl	4(%esp)
	movl	4(%esp), %eax
	movl	%ebp, 12(%esp)
	cmpl	%eax, %edx
	jge	.L58
	.p2align 4,,7
	.p2align 3
.L64:
	leal	1(%edx), %eax
	movl	%edx, %ebx
	leal	(%eax,%eax), %edx
	sall	$5, %eax
	addl	%ecx, %eax
	movl	8(%eax), %ebp
	leal	-1(%edx), %esi
	movl	%esi, %edi
	sall	$4, %edi
	addl	%ecx, %edi
	movl	%ebp, (%esp)
	movl	12(%edi), %ebp
	cmpl	%ebp, 12(%eax)
	jg	.L59
	jl	.L65
	movl	(%esp), %ebp
	cmpl	8(%edi), %ebp
	jae	.L59
.L65:
	movl	%esi, %eax
	movl	%esi, %edx
	sall	$4, %eax
	addl	%ecx, %eax
.L59:
	movl	(%eax), %esi
	sall	$4, %ebx
	addl	%ecx, %ebx
	cmpl	4(%esp), %edx
	movl	%esi, (%ebx)
	movl	4(%eax), %esi
	movl	%esi, 4(%ebx)
	movl	8(%eax), %esi
	movl	%esi, 8(%ebx)
	movl	12(%eax), %eax
	movl	%eax, 12(%ebx)
	jl	.L64
.L58:
	testb	$1, 12(%esp)
	jne	.L62
	movl	12(%esp), %eax
	subl	$2, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%ebx, %eax
	sarl	%eax
	cmpl	%eax, %edx
	je	.L66
.L62:
	movl	8(%esp), %eax
	movl	%edx, 52(%esp)
	movl	%ecx, 48(%esp)
	movl	%eax, 56(%esp)
	addl	$28, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	jmp	_ZSt11__push_heapIP5QueryiS0_EvT_T0_S3_T1_
	.p2align 4,,7
	.p2align 3
.L66:
	.cfi_restore_state
	movl	%edx, %eax
	leal	1(%edx,%edx), %edx
	movl	%edx, %ebx
	sall	$4, %ebx
	addl	%ecx, %ebx
	movl	(%ebx), %esi
	sall	$4, %eax
	addl	%ecx, %eax
	movl	%esi, (%eax)
	movl	4(%ebx), %esi
	movl	%esi, 4(%eax)
	movl	8(%ebx), %esi
	movl	%esi, 8(%eax)
	movl	12(%ebx), %ebx
	movl	%ebx, 12(%eax)
	jmp	.L62
	.cfi_endproc
.LFE450:
	.size	_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_, .-_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_
	.section	.text._ZSt13__heap_selectIP5QueryEvT_S2_S2_,"axG",@progbits,_ZSt13__heap_selectIP5QueryEvT_S2_S2_,comdat
	.p2align 4,,15
	.weak	_ZSt13__heap_selectIP5QueryEvT_S2_S2_
	.type	_ZSt13__heap_selectIP5QueryEvT_S2_S2_, @function
_ZSt13__heap_selectIP5QueryEvT_S2_S2_:
.LFB439:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$76, %esp
	.cfi_def_cfa_offset 96
	movl	96(%esp), %ebx
	movl	100(%esp), %eax
	subl	%ebx, %eax
	cmpl	$31, %eax
	movl	%eax, 44(%esp)
	jle	.L71
	movl	44(%esp), %eax
	sarl	$4, %eax
	movl	%eax, %edi
	subl	$2, %edi
	sarl	%edi
	movl	%edi, %esi
	sall	$4, %esi
	movl	%eax, 40(%esp)
	addl	%ebx, %esi
	jmp	.L72
	.p2align 4,,7
	.p2align 3
.L81:
	subl	$1, %edi
.L72:
	movl	8(%esi), %edx
	movl	(%esi), %ebp
	movl	4(%esi), %ecx
	movl	12(%esi), %eax
	subl	$16, %esi
	movl	%edx, 56(%esp)
	movl	%edx, 20(%esp)
	movl	40(%esp), %edx
	movl	%ebp, 48(%esp)
	movl	%ecx, 52(%esp)
	movl	%eax, 60(%esp)
	movl	%ebp, 12(%esp)
	movl	%ecx, 16(%esp)
	movl	%eax, 24(%esp)
	movl	%edx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%ebx, (%esp)
	call	_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_
	testl	%edi, %edi
	jne	.L81
.L71:
	movl	44(%esp), %edx
	movl	100(%esp), %esi
	movl	104(%esp), %edi
	sarl	$4, %edx
	cmpl	104(%esp), %esi
	movl	%edx, 44(%esp)
	jae	.L67
	.p2align 4,,7
	.p2align 3
.L77:
	movl	12(%ebx), %edx
	cmpl	%edx, 12(%esi)
	movl	8(%esi), %eax
	jg	.L73
	jl	.L76
	cmpl	8(%ebx), %eax
	jae	.L73
.L76:
	movl	12(%esi), %eax
	movl	8(%esi), %edx
	movl	(%esi), %ebp
	movl	4(%esi), %ecx
	movl	%eax, 60(%esp)
	movl	%eax, 24(%esp)
	movl	(%ebx), %eax
	movl	%edx, 56(%esp)
	movl	%ebp, 48(%esp)
	movl	%ecx, 52(%esp)
	movl	%eax, (%esi)
	movl	4(%ebx), %eax
	movl	%eax, 4(%esi)
	movl	8(%ebx), %eax
	movl	%eax, 8(%esi)
	movl	12(%ebx), %eax
	movl	%eax, 12(%esi)
	movl	%edx, 20(%esp)
	movl	44(%esp), %edx
	movl	%ebp, 12(%esp)
	movl	%ecx, 16(%esp)
	movl	$0, 4(%esp)
	movl	%edx, 8(%esp)
	movl	%ebx, (%esp)
	call	_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_
.L73:
	addl	$16, %esi
	cmpl	%esi, %edi
	ja	.L77
.L67:
	addl	$76, %esp
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE439:
	.size	_ZSt13__heap_selectIP5QueryEvT_S2_S2_, .-_ZSt13__heap_selectIP5QueryEvT_S2_S2_
	.section	.text._ZSt16__introsort_loopIP5QueryiEvT_S2_T0_,"axG",@progbits,_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_,comdat
	.p2align 4,,15
	.weak	_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_
	.type	_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_, @function
_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_:
.LFB433:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$76, %esp
	.cfi_def_cfa_offset 96
	movl	96(%esp), %ebp
	movl	100(%esp), %eax
	subl	%ebp, %eax
	cmpl	$271, %eax
	jle	.L82
	movl	104(%esp), %edx
	testl	%edx, %edx
	je	.L98
	leal	16(%ebp), %edx
	movl	%edx, 44(%esp)
.L85:
	movl	100(%esp), %edx
	sarl	$5, %eax
	sall	$4, %eax
	addl	%ebp, %eax
	movl	%eax, 4(%esp)
	subl	$16, %edx
	subl	$1, 104(%esp)
	movl	%edx, 8(%esp)
	movl	%ebp, (%esp)
	call	_ZSt19__move_median_firstIP5QueryEvT_S2_S2_
	movl	100(%esp), %eax
	movl	44(%esp), %ebx
	jmp	.L97
	.p2align 4,,7
	.p2align 3
.L100:
	movl	40(%esp), %eax
	.p2align 4,,7
	.p2align 3
.L91:
	cmpl	%eax, %ebx
	jae	.L113
	.p2align 4,,7
	.p2align 3
.L95:
	movl	4(%ebx), %edx
	movl	(%ebx), %edi
	movl	%edx, 40(%esp)
	movl	(%eax), %edx
	movl	%edx, (%ebx)
	movl	4(%eax), %edx
	movl	%edx, 4(%ebx)
	movl	8(%eax), %edx
	movl	%edx, 8(%ebx)
	movl	12(%eax), %edx
	movl	%edx, 12(%ebx)
	addl	$16, %ebx
	movl	%edi, (%eax)
	movl	40(%esp), %edi
	movl	%esi, 8(%eax)
	movl	%ecx, 12(%eax)
	movl	%edi, 4(%eax)
.L97:
	movl	8(%ebp), %edx
	movl	12(%ebx), %ecx
	movl	8(%ebx), %esi
	movl	%edx, 36(%esp)
	movl	12(%ebp), %edx
	cmpl	%edx, %ecx
	jg	.L87
	jl	.L110
	cmpl	36(%esp), %esi
	jae	.L87
.L110:
	movl	36(%esp), %edi
	.p2align 4,,7
	.p2align 3
.L108:
	addl	$16, %ebx
	movl	12(%ebx), %ecx
	movl	8(%ebx), %esi
	cmpl	%edx, %ecx
	jl	.L108
	jg	.L111
	cmpl	%edi, %esi
	jb	.L108
.L111:
	movl	%edi, 36(%esp)
.L87:
	cmpl	%edx, -4(%eax)
	leal	-16(%eax), %edi
	movl	%edi, 40(%esp)
	jl	.L100
	jg	.L101
	movl	36(%esp), %edi
	cmpl	%edi, -8(%eax)
	jbe	.L100
.L101:
	movl	40(%esp), %eax
	movl	36(%esp), %edi
	.p2align 4,,7
	.p2align 3
.L109:
	subl	$16, %eax
	cmpl	%edx, 12(%eax)
	jg	.L109
	jl	.L91
	cmpl	%edi, 8(%eax)
	ja	.L109
	cmpl	%eax, %ebx
	.p2align 4,,6
	jb	.L95
.L113:
	movl	104(%esp), %eax
	movl	100(%esp), %edx
	movl	%ebx, (%esp)
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	call	_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_
	movl	%ebx, %eax
	subl	%ebp, %eax
	cmpl	$271, %eax
	jle	.L82
	movl	104(%esp), %ecx
	movl	%ebx, 100(%esp)
	testl	%ecx, %ecx
	jne	.L85
.L98:
	movl	100(%esp), %eax
	movl	%ebp, (%esp)
	movl	%eax, 8(%esp)
	movl	%eax, 4(%esp)
	call	_ZSt13__heap_selectIP5QueryEvT_S2_S2_
	movl	100(%esp), %ebx
.L86:
	movl	0(%ebp), %esi
	subl	$16, %ebx
	movl	(%ebx), %edi
	movl	4(%ebx), %ecx
	movl	8(%ebx), %edx
	movl	%esi, (%ebx)
	movl	4(%ebp), %esi
	movl	12(%ebx), %eax
	movl	%edi, 48(%esp)
	movl	%ecx, 52(%esp)
	movl	%esi, 4(%ebx)
	movl	8(%ebp), %esi
	movl	%eax, 60(%esp)
	movl	%edx, 56(%esp)
	movl	%esi, 8(%ebx)
	movl	12(%ebp), %esi
	movl	%esi, 12(%ebx)
	movl	%ebx, %esi
	subl	%ebp, %esi
	movl	%eax, 24(%esp)
	movl	%esi, %eax
	sarl	$4, %eax
	movl	%edi, 12(%esp)
	movl	%ecx, 16(%esp)
	movl	%edx, 20(%esp)
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	%ebp, (%esp)
	call	_ZSt13__adjust_heapIP5QueryiS0_EvT_T0_S3_T1_
	cmpl	$31, %esi
	jg	.L86
.L82:
	addl	$76, %esp
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE433:
	.size	_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_, .-_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d%d%d%d%d%d%d%d"
.LC1:
	.string	"%lld%lld"
	.globl	__moddi3
	.globl	__divdi3
.LC2:
	.string	"%lld\n"
	.text
	.p2align 4,,15
	.globl	_Z5solvev
	.type	_Z5solvev, @function
_Z5solvev:
.LFB430:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$252, %esp
	.cfi_def_cfa_offset 272
	movl	$160080, 8(%esp)
	movl	$0, 4(%esp)
	movl	$ans, (%esp)
	call	memset
	movl	$80056, 8(%esp)
	movl	$0, 4(%esp)
	movl	$hashPos, (%esp)
	call	memset
	movl	$80056, 8(%esp)
	movl	$0, 4(%esp)
	movl	$hashAcc, (%esp)
	call	memset
	leal	236(%esp), %eax
	movl	%eax, 32(%esp)
	leal	232(%esp), %eax
	movl	%eax, 28(%esp)
	leal	228(%esp), %eax
	movl	%eax, 24(%esp)
	leal	224(%esp), %eax
	movl	%eax, 20(%esp)
	leal	220(%esp), %eax
	movl	%eax, 16(%esp)
	leal	216(%esp), %eax
	movl	%eax, 12(%esp)
	leal	212(%esp), %eax
	movl	%eax, 8(%esp)
	leal	208(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	scanf
	movl	236(%esp), %eax
	testl	%eax, %eax
	jle	.L115
	movl	$query+8, %ebx
	xorl	%esi, %esi
	leal	200(%esp), %edi
	leal	192(%esp), %ebp
	.p2align 4,,7
	.p2align 3
.L116:
	movl	%edi, 8(%esp)
	movl	%ebp, 4(%esp)
	movl	$.LC1, (%esp)
	call	scanf
	movl	192(%esp), %eax
	movl	196(%esp), %edx
	movl	%esi, -8(%ebx)
	movl	%esi, 8(%ebx)
	addl	$-1, %eax
	movl	%eax, (%ebx)
	movl	200(%esp), %eax
	adcl	$-1, %edx
	movl	%edx, 4(%ebx)
	movl	204(%esp), %edx
	addl	$1, %esi
	movl	$-1, -4(%ebx)
	movl	$1, 12(%ebx)
	movl	%eax, 16(%ebx)
	movl	236(%esp), %eax
	movl	%edx, 20(%ebx)
	addl	$32, %ebx
	cmpl	%esi, %eax
	jg	.L116
.L115:
	leal	(%eax,%eax), %ecx
	sall	$5, %eax
	addl	$query, %eax
	cmpl	$query, %eax
	movl	%ecx, 84(%esp)
	movl	%eax, 168(%esp)
	je	.L117
	movl	%eax, %ebx
	movl	168(%esp), %ecx
	movl	$31, %eax
	subl	$query, %ebx
	movl	%ebx, %edx
	sarl	$4, %edx
	bsrl	%edx, %edx
	xorl	$31, %edx
	subl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	$query, (%esp)
	call	_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_
	cmpl	$271, %ebx
	jle	.L118
	movl	$query+256, 4(%esp)
	movl	$query, (%esp)
	call	_ZSt16__insertion_sortIP5QueryEvT_S2_
	cmpl	$query+256, 168(%esp)
	je	.L117
	movl	168(%esp), %esi
	movl	$query+256, %ebx
.L119:
	movl	%ebx, (%esp)
	addl	$16, %ebx
	call	_ZSt25__unguarded_linear_insertIP5QueryEvT_
	cmpl	%ebx, %esi
	jne	.L119
.L117:
	movl	212(%esp), %ecx
	movl	208(%esp), %edi
	movl	84(%esp), %esi
	movl	%ecx, %edx
	movl	%edi, %eax
	sarl	$31, %eax
	sarl	$31, %edx
	testl	%esi, %esi
	movl	%edi, 72(%esp)
	movl	%eax, 76(%esp)
	movl	%ecx, 64(%esp)
	movl	%ecx, 96(%esp)
	movl	%edx, 100(%esp)
	je	.L164
	movl	query+12, %ebx
	movl	query+8, %ecx
	movl	$0, 80(%esp)
	movl	%ebx, %edx
	orl	%ecx, %edx
	je	.L181
	.p2align 4,,7
	.p2align 3
.L122:
	movl	232(%esp), %edx
	movl	$0, 60(%esp)
	movl	%edx, %eax
	movl	%edx, 136(%esp)
	sarl	$31, %edx
	movl	%eax, 88(%esp)
	movl	136(%esp), %eax
	movl	%edx, 92(%esp)
	movl	76(%esp), %edx
	xorl	92(%esp), %edx
	xorl	%edi, %eax
	orl	%edx, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 56(%esp)
	movl	%ecx, %eax
	xorl	$1, %eax
	orl	%ebx, %eax
	je	.L187
.L125:
	movl	64(%esp), %eax
	movl	100(%esp), %edx
	xorl	136(%esp), %eax
	xorl	92(%esp), %edx
	movl	$0, 68(%esp)
	orl	%edx, %eax
	movl	60(%esp), %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 64(%esp)
	movl	56(%esp), %eax
	addl	%eax, 64(%esp)
	movl	%ecx, %eax
	adcl	%edx, 68(%esp)
	xorl	$2, %eax
	orl	%ebx, %eax
	je	.L188
.L127:
	movl	228(%esp), %ecx
	movl	%ecx, %eax
	imull	%ecx, %eax
	addl	$1, %eax
	cmpl	$2, %eax
	movl	%eax, 160(%esp)
	jle	.L129
	movl	216(%esp), %ebx
	movl	%ecx, 128(%esp)
	movl	$3, 104(%esp)
	movl	$0, 108(%esp)
	movl	%ebx, %edx
	movl	%ebx, 180(%esp)
	sarl	$31, %edx
	movl	%ebx, 112(%esp)
	movl	220(%esp), %ebx
	movl	%edx, 116(%esp)
	movl	%ebx, 184(%esp)
	movl	%ebx, %edx
	movl	%ebx, 120(%esp)
	movl	224(%esp), %ebx
	sarl	$31, %edx
	movl	%edx, 124(%esp)
	movl	%ebx, %edx
	sarl	$31, %edx
	movl	%edx, 156(%esp)
	movl	%ecx, %edx
	movl	72(%esp), %ecx
	sarl	$31, %edx
	movl	%ebx, 188(%esp)
	movl	%ebx, 152(%esp)
	movl	76(%esp), %ebx
	movl	%edx, 132(%esp)
	jmp	.L135
	.p2align 4,,7
	.p2align 3
.L130:
	movl	92(%esp), %eax
	movl	88(%esp), %edx
	xorl	176(%esp), %eax
	xorl	140(%esp), %edx
	orl	%edx, %eax
	je	.L189
	addl	$1, 104(%esp)
	movl	104(%esp), %ebx
	adcl	$0, 108(%esp)
	cmpl	%ebx, 160(%esp)
	jl	.L129
	movl	140(%esp), %eax
	movl	176(%esp), %edx
	movl	96(%esp), %ecx
	movl	100(%esp), %ebx
	movl	%eax, 96(%esp)
	movl	%edx, 100(%esp)
.L135:
	movl	104(%esp), %eax
	movl	100(%esp), %edx
	imull	112(%esp), %edx
	movl	%eax, 144(%esp)
	movl	116(%esp), %eax
	imull	96(%esp), %eax
	leal	(%eax,%edx), %esi
	movl	112(%esp), %eax
	mull	96(%esp)
	addl	%esi, %edx
	movl	%eax, 56(%esp)
	movl	120(%esp), %eax
	movl	%edx, 60(%esp)
	movl	124(%esp), %edx
	imull	%ebx, %eax
	imull	%ecx, %edx
	leal	(%edx,%eax), %ebx
	movl	120(%esp), %eax
	mull	%ecx
	movl	128(%esp), %ecx
	addl	%ebx, %edx
	movl	132(%esp), %ebx
	movl	%eax, 72(%esp)
	movl	72(%esp), %eax
	movl	%edx, 76(%esp)
	movl	76(%esp), %edx
	addl	56(%esp), %eax
	adcl	60(%esp), %edx
	addl	152(%esp), %eax
	adcl	156(%esp), %edx
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	__moddi3
	movl	80(%esp), %ebx
	movl	%eax, 140(%esp)
	movl	88(%esp), %eax
	movl	%edx, 176(%esp)
	movl	92(%esp), %edx
	xorl	140(%esp), %eax
	xorl	176(%esp), %edx
	orl	%edx, %eax
	sete	%al
	xorl	%edx, %edx
	movzbl	%al, %eax
	addl	%eax, 64(%esp)
	adcl	%edx, 68(%esp)
	cmpl	%ebx, 84(%esp)
	je	.L130
	movl	%ebx, %eax
	movl	104(%esp), %edx
	sall	$4, %eax
	movl	query+8(%eax), %edi
	movl	query+12(%eax), %esi
	movl	108(%esp), %eax
	xorl	%edi, %edx
	xorl	%esi, %eax
	orl	%edx, %eax
	jne	.L130
	addl	$1, %ebx
	movl	%ebx, %ecx
	sall	$4, %ecx
	addl	$query+8, %ecx
	.p2align 4,,7
	.p2align 3
.L131:
	movl	80(%esp), %eax
	movl	%ebx, 80(%esp)
	sall	$4, %eax
	movl	query(%eax), %ebp
	movl	query+4(%eax), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	movl	%eax, 52(%esp)
	movl	%edx, 60(%esp)
	movl	68(%esp), %edx
	movl	60(%esp), %eax
	imull	52(%esp), %edx
	imull	64(%esp), %eax
	addl	%edx, %eax
	movl	%eax, 56(%esp)
	movl	64(%esp), %eax
	mull	52(%esp)
	movl	%eax, 72(%esp)
	movl	56(%esp), %eax
	addl	%eax, %edx
	movl	72(%esp), %eax
	addl	%eax, ans(,%ebp,8)
	movl	%edx, 76(%esp)
	movl	76(%esp), %edx
	adcl	%edx, ans+4(,%ebp,8)
	cmpl	%ebx, 84(%esp)
	je	.L130
	addl	$16, %ecx
	movl	-12(%ecx), %eax
	movl	-16(%ecx), %edx
	xorl	%esi, %eax
	xorl	%edi, %edx
	orl	%edx, %eax
	jne	.L130
	addl	$1, %ebx
	jmp	.L131
	.p2align 4,,7
	.p2align 3
.L188:
	movl	80(%esp), %edi
	addl	$1, %edi
	movl	%edi, %ecx
	sall	$4, %ecx
	addl	$query+8, %ecx
.L163:
	movl	80(%esp), %eax
	movl	68(%esp), %esi
	movl	%edi, 80(%esp)
	sall	$4, %eax
	movl	query+4(%eax), %ebp
	movl	query(%eax), %ebx
	movl	%ebp, %eax
	sarl	$31, %eax
	movl	%eax, 60(%esp)
	movl	60(%esp), %eax
	imull	%ebp, %esi
	imull	64(%esp), %eax
	addl	%eax, %esi
	movl	64(%esp), %eax
	mull	%ebp
	addl	%esi, %edx
	movl	%eax, 56(%esp)
	movl	56(%esp), %eax
	addl	%eax, ans(,%ebx,8)
	movl	%edx, 60(%esp)
	movl	60(%esp), %edx
	adcl	%edx, ans+4(,%ebx,8)
	cmpl	%edi, 84(%esp)
	je	.L127
	addl	$16, %ecx
	movl	-16(%ecx), %eax
	xorl	$2, %eax
	orl	-12(%ecx), %eax
	jne	.L127
	addl	$1, %edi
	jmp	.L163
	.p2align 4,,7
	.p2align 3
.L187:
	movl	80(%esp), %edi
	addl	$1, %edi
	movl	%edi, %esi
	sall	$4, %esi
	addl	$query+8, %esi
.L162:
	movl	80(%esp), %eax
	movl	56(%esp), %ebp
	movl	%edi, 80(%esp)
	sall	$4, %eax
	movl	query+4(%eax), %ecx
	movl	query(%eax), %ebx
	movl	56(%esp), %eax
	movl	%ecx, %edx
	sarl	$31, %edx
	imull	%edx, %ebp
	mull	%ecx
	addl	%ebp, %edx
	movl	%edx, 108(%esp)
	movl	108(%esp), %ecx
	movl	%eax, 104(%esp)
	movl	104(%esp), %edx
	addl	%edx, ans(,%ebx,8)
	adcl	%ecx, ans+4(,%ebx,8)
	cmpl	%edi, 84(%esp)
	je	.L124
	addl	$16, %esi
	movl	-16(%esi), %ecx
	movl	-12(%esi), %ebx
	movl	%ecx, %eax
	xorl	$1, %eax
	orl	%ebx, %eax
	jne	.L125
	addl	$1, %edi
	jmp	.L162
	.p2align 4,,7
	.p2align 3
.L190:
	movl	%esi, 80(%esp)
	movl	%edx, %edi
.L120:
	movl	232(%esp), %ecx
	movl	$0, 60(%esp)
	movl	%ecx, %edx
	movl	%ecx, %eax
	sarl	$31, %edx
	xorl	%edi, %eax
	movl	%edx, 92(%esp)
	movl	76(%esp), %edx
	xorl	92(%esp), %edx
	movl	%ecx, 136(%esp)
	movl	%ecx, 88(%esp)
	orl	%edx, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 56(%esp)
.L124:
	movl	64(%esp), %eax
	movl	100(%esp), %edx
	xorl	88(%esp), %eax
	xorl	92(%esp), %edx
	movl	56(%esp), %ecx
	movl	60(%esp), %ebx
	orl	%edx, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, 64(%esp)
	addl	%ecx, 64(%esp)
	movl	$0, 68(%esp)
	adcl	%ebx, 68(%esp)
	jmp	.L127
.L189:
	movl	144(%esp), %eax
	movl	96(%esp), %ecx
	subl	$1, %eax
	movl	%eax, %edx
	sarl	$31, %edx
	movl	%eax, hashPos(,%ecx,8)
	movl	64(%esp), %eax
	movl	%edx, hashPos+4(,%ecx,8)
	movl	68(%esp), %edx
	addl	$-1, %eax
	adcl	$-1, %edx
	movl	%eax, hashAcc(,%ecx,8)
	movl	%edx, hashAcc+4(,%ecx,8)
	movl	144(%esp), %ecx
	movl	%ecx, %ebx
	movl	%ecx, %esi
	movl	144(%esp), %ecx
	sarl	$31, %ebx
	andl	%ebx, %ecx
	cmpl	$-1, %ecx
	je	.L129
	movl	160(%esp), %eax
	movl	%esi, %ecx
	addl	$1, %ecx
	adcl	$0, %ebx
	movl	%ecx, 144(%esp)
	movl	%eax, %edx
	sarl	$31, %edx
	cmpl	%edx, %ebx
	movl	%ebx, 148(%esp)
	movl	%eax, 152(%esp)
	movl	%edx, 156(%esp)
	jg	.L144
	jl	.L170
	movl	160(%esp), %ebx
	cmpl	%ebx, %ecx
	jbe	.L170
.L144:
	movl	80(%esp), %ecx
	cmpl	%ecx, 84(%esp)
	jle	.L129
.L172:
	movl	%ecx, %eax
	movl	68(%esp), %edx
	sall	$4, %eax
	movl	64(%esp), %esi
	movl	query(%eax), %ebx
	movl	query+4(%eax), %eax
	movl	%eax, %edi
	sarl	$31, %edi
	imull	%eax, %edx
	imull	%edi, %esi
	addl	%edx, %esi
	mull	64(%esp)
	addl	%esi, %edx
	addl	%eax, ans(,%ebx,8)
	adcl	%edx, ans+4(,%ebx,8)
	addl	$1, %ecx
	cmpl	84(%esp), %ecx
	jne	.L172
.L129:
	movl	236(%esp), %ebx
	testl	%ebx, %ebx
	jle	.L114
	xorl	%ebx, %ebx
	.p2align 4,,7
	.p2align 3
.L159:
	movl	ans(,%ebx,8), %eax
	movl	ans+4(,%ebx,8), %edx
	addl	$1, %ebx
	movl	$.LC2, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	call	__printf_chk
	cmpl	%ebx, 236(%esp)
	jg	.L159
.L114:
	addl	$252, %esp
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.L181:
	.cfi_restore_state
	movl	80(%esp), %esi
	movl	%edi, %edx
	.p2align 4,,7
	.p2align 3
.L180:
	addl	$1, %esi
	cmpl	%esi, 84(%esp)
	je	.L190
	movl	%esi, %eax
	sall	$4, %eax
	movl	query+12(%eax), %ebx
	movl	query+8(%eax), %ecx
	movl	%ebx, %eax
	orl	%ecx, %eax
	je	.L180
	movl	%esi, 80(%esp)
	movl	%edx, %edi
	jmp	.L122
.L118:
	movl	168(%esp), %ebx
	movl	$query, (%esp)
	movl	%ebx, 4(%esp)
	call	_ZSt16__insertion_sortIP5QueryEvT_S2_
	jmp	.L117
.L170:
	movl	180(%esp), %eax
	movl	96(%esp), %ecx
	movl	100(%esp), %ebx
	movl	%eax, %edx
	movl	%eax, 112(%esp)
	movl	184(%esp), %eax
	sarl	$31, %edx
	movl	%edx, 116(%esp)
	movl	%eax, 120(%esp)
	movl	%eax, %edx
	movl	188(%esp), %eax
	sarl	$31, %edx
	movl	%edx, 124(%esp)
	movl	%eax, %edx
	sarl	$31, %edx
	movl	%eax, 160(%esp)
	movl	%edx, 164(%esp)
	jmp	.L145
	.p2align 4,,7
	.p2align 3
.L141:
	addl	$1, 144(%esp)
	adcl	$0, 148(%esp)
	movl	156(%esp), %ebx
	cmpl	%ebx, 148(%esp)
	jl	.L167
	jg	.L144
	movl	152(%esp), %eax
	cmpl	%eax, 144(%esp)
	ja	.L144
.L167:
	movl	96(%esp), %edx
	movl	104(%esp), %eax
	movl	140(%esp), %ecx
	movl	176(%esp), %ebx
	movl	%edx, 140(%esp)
	movl	%eax, 176(%esp)
.L145:
	movl	116(%esp), %eax
	movl	176(%esp), %edx
	imull	140(%esp), %eax
	imull	112(%esp), %edx
	leal	(%eax,%edx), %esi
	movl	112(%esp), %eax
	mull	140(%esp)
	addl	%esi, %edx
	movl	%eax, 56(%esp)
	movl	120(%esp), %eax
	movl	%edx, 60(%esp)
	movl	124(%esp), %edx
	imull	%ebx, %eax
	imull	%ecx, %edx
	leal	(%edx,%eax), %ebx
	movl	120(%esp), %eax
	mull	%ecx
	movl	128(%esp), %ecx
	addl	%ebx, %edx
	movl	132(%esp), %ebx
	movl	%eax, 72(%esp)
	movl	72(%esp), %eax
	movl	%edx, 76(%esp)
	movl	76(%esp), %edx
	addl	56(%esp), %eax
	adcl	60(%esp), %edx
	addl	160(%esp), %eax
	adcl	164(%esp), %edx
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	__moddi3
	movl	80(%esp), %ebx
	movl	%eax, 96(%esp)
	movl	88(%esp), %eax
	movl	%edx, 104(%esp)
	movl	92(%esp), %edx
	xorl	96(%esp), %eax
	xorl	104(%esp), %edx
	orl	%edx, %eax
	sete	%al
	xorl	%edx, %edx
	movzbl	%al, %eax
	addl	%eax, 64(%esp)
	adcl	%edx, 68(%esp)
	cmpl	%ebx, 84(%esp)
	je	.L138
	movl	%ebx, %eax
	movl	144(%esp), %edx
	sall	$4, %eax
	movl	query+8(%eax), %edi
	movl	query+12(%eax), %esi
	movl	148(%esp), %eax
	xorl	%edi, %edx
	xorl	%esi, %eax
	orl	%edx, %eax
	je	.L191
	.p2align 4,,7
	.p2align 3
.L138:
	movl	92(%esp), %eax
	movl	88(%esp), %edx
	xorl	104(%esp), %eax
	xorl	96(%esp), %edx
	orl	%edx, %eax
	jne	.L141
	movl	140(%esp), %ecx
	movl	hashPos+4(,%ecx,8), %edx
	movl	hashPos(,%ecx,8), %eax
	movl	%edx, %ebx
	orl	%eax, %ebx
	jne	.L192
	movl	144(%esp), %eax
	movl	140(%esp), %ecx
	movl	148(%esp), %edx
	addl	$-1, %eax
	movl	%eax, hashPos(,%ecx,8)
	movl	64(%esp), %eax
	adcl	$-1, %edx
	movl	%edx, hashPos+4(,%ecx,8)
	movl	68(%esp), %edx
	addl	$-1, %eax
	movl	%eax, hashAcc(,%ecx,8)
	adcl	$-1, %edx
	movl	%edx, hashAcc+4(,%ecx,8)
	jmp	.L141
.L191:
	addl	$1, %ebx
	movl	%ebx, %ecx
	sall	$4, %ecx
	addl	$query+8, %ecx
	jmp	.L139
.L195:
	addl	$1, %ebx
.L139:
	movl	80(%esp), %eax
	movl	%ebx, 80(%esp)
	sall	$4, %eax
	movl	query(%eax), %ebp
	movl	query+4(%eax), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	movl	%eax, 180(%esp)
	movl	%edx, 60(%esp)
	movl	68(%esp), %edx
	movl	60(%esp), %eax
	imull	180(%esp), %edx
	imull	64(%esp), %eax
	addl	%edx, %eax
	movl	%eax, 56(%esp)
	movl	64(%esp), %eax
	mull	180(%esp)
	movl	%eax, 72(%esp)
	movl	56(%esp), %eax
	addl	%eax, %edx
	movl	72(%esp), %eax
	addl	%eax, ans(,%ebp,8)
	movl	%edx, 76(%esp)
	movl	76(%esp), %edx
	adcl	%edx, ans+4(,%ebp,8)
	cmpl	%ebx, 84(%esp)
	je	.L138
	addl	$16, %ecx
	movl	-12(%ecx), %eax
	movl	-16(%ecx), %edx
	xorl	%esi, %eax
	xorl	%edi, %edx
	orl	%edx, %eax
	jne	.L138
	jmp	.L195
.L164:
	movl	$0, 80(%esp)
	jmp	.L120
.L192:
	movl	%eax, 104(%esp)
	movl	176(%esp), %eax
	movl	%edx, 108(%esp)
	andl	%ecx, %eax
	cmpl	$-1, %eax
	je	.L144
	movl	144(%esp), %ecx
	movl	148(%esp), %ebx
	addl	$-1, %ecx
	adcl	$-1, %ebx
	movl	%ebx, 156(%esp)
	movl	140(%esp), %ebx
	movl	%ecx, 152(%esp)
	movl	hashAcc(,%ebx,8), %ecx
	movl	hashAcc+4(,%ebx,8), %ebx
	movl	%ecx, 56(%esp)
	movl	64(%esp), %ecx
	movl	%ebx, 60(%esp)
	movl	68(%esp), %ebx
	addl	$-1, %ecx
	adcl	$-1, %ebx
	movl	%ecx, 64(%esp)
	movl	56(%esp), %ecx
	subl	%ecx, 64(%esp)
	movl	152(%esp), %ecx
	movl	%ebx, 68(%esp)
	movl	60(%esp), %ebx
	sbbl	%ebx, 68(%esp)
	movl	156(%esp), %ebx
	subl	104(%esp), %ecx
	sbbl	108(%esp), %ebx
	movl	%ecx, 112(%esp)
	movl	%ebx, 116(%esp)
	movl	80(%esp), %ebx
	cmpl	%ebx, 84(%esp)
	jle	.L148
	movl	%ebx, %ebp
	sall	$4, %ebp
	addl	$query+8, %ebp
	movl	%ebx, 72(%esp)
	.p2align 4,,7
	.p2align 3
.L149:
	movl	72(%esp), %eax
	movl	0(%ebp), %esi
	movl	4(%ebp), %edi
	sall	$4, %eax
	movl	query+4(%eax), %ebx
	movl	query(%eax), %ecx
	movl	%ebx, %eax
	sarl	$31, %eax
	movl	%eax, 100(%esp)
	movl	60(%esp), %eax
	movl	100(%esp), %edx
	subl	104(%esp), %esi
	sbbl	108(%esp), %edi
	imull	%ebx, %eax
	imull	56(%esp), %edx
	movl	%ecx, 88(%esp)
	movl	%esi, (%esp)
	movl	%edi, 4(%esp)
	leal	(%eax,%edx), %ecx
	movl	56(%esp), %eax
	movl	%ebx, 96(%esp)
	mull	%ebx
	movl	%eax, 120(%esp)
	movl	88(%esp), %eax
	addl	%ecx, %edx
	movl	%edx, 124(%esp)
	movl	120(%esp), %edx
	movl	124(%esp), %ecx
	addl	ans(,%eax,8), %edx
	adcl	ans+4(,%eax,8), %ecx
	movl	%edx, 120(%esp)
	movl	112(%esp), %edx
	movl	%ecx, 124(%esp)
	movl	116(%esp), %ecx
	movl	%edx, 8(%esp)
	movl	%ecx, 12(%esp)
	call	__divdi3
	imull	64(%esp), %edx
	movl	%eax, %ecx
	movl	68(%esp), %eax
	imull	%ecx, %eax
	addl	%edx, %eax
	movl	%eax, 128(%esp)
	movl	64(%esp), %eax
	mull	%ecx
	movl	128(%esp), %ecx
	addl	%ecx, %edx
	movl	%eax, 160(%esp)
	movl	%edx, %ecx
	movl	100(%esp), %eax
	imull	160(%esp), %eax
	imull	%ebx, %ecx
	movl	%edx, 164(%esp)
	addl	%eax, %ecx
	movl	160(%esp), %eax
	mull	%ebx
	addl	%ecx, %edx
	movl	%eax, 96(%esp)
	movl	88(%esp), %ecx
	movl	%edx, 100(%esp)
	movl	96(%esp), %eax
	movl	100(%esp), %edx
	addl	120(%esp), %eax
	adcl	124(%esp), %edx
	movl	116(%esp), %ebx
	movl	%eax, ans(,%ecx,8)
	movl	%edx, ans+4(,%ecx,8)
	movl	112(%esp), %ecx
	movl	%esi, (%esp)
	movl	%ebx, 12(%esp)
	movl	%edi, 4(%esp)
	movl	%ecx, 8(%esp)
	call	__moddi3
	movl	84(%esp), %ebx
	addl	104(%esp), %eax
	adcl	108(%esp), %edx
	addl	$1, 72(%esp)
	movl	%eax, 0(%ebp)
	movl	%edx, 4(%ebp)
	addl	$16, %ebp
	cmpl	%ebx, 72(%esp)
	jne	.L149
.L148:
	movl	80(%esp), %ebx
	sall	$4, %ebx
	addl	$query, %ebx
	cmpl	%ebx, 168(%esp)
	je	.L150
	movl	168(%esp), %esi
	movl	$31, %edx
	movl	168(%esp), %ecx
	movl	%ebx, (%esp)
	subl	%ebx, %esi
	movl	%esi, %eax
	sarl	$4, %eax
	bsrl	%eax, %eax
	xorl	$31, %eax
	subl	%eax, %edx
	addl	%edx, %edx
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	call	_ZSt16__introsort_loopIP5QueryiEvT_S2_T0_
	cmpl	$271, %esi
	jle	.L151
	leal	256(%ebx), %esi
	movl	%esi, 4(%esp)
	movl	%ebx, (%esp)
	call	_ZSt16__insertion_sortIP5QueryEvT_S2_
	cmpl	%esi, 168(%esp)
	je	.L186
.L173:
	movl	%esi, (%esp)
	addl	$16, %esi
	call	_ZSt25__unguarded_linear_insertIP5QueryEvT_
	cmpl	%esi, 168(%esp)
	jne	.L173
.L186:
	movl	140(%esp), %ebx
	movl	hashAcc(,%ebx,8), %ecx
	movl	hashAcc+4(,%ebx,8), %ebx
	movl	%ecx, 56(%esp)
	movl	232(%esp), %ecx
	movl	%ebx, 60(%esp)
	movl	%ecx, 136(%esp)
.L150:
	movl	104(%esp), %ecx
	movl	108(%esp), %ebx
	addl	$1, %ecx
	adcl	$0, %ebx
	cmpl	%ebx, 156(%esp)
	movl	%ecx, 104(%esp)
	movl	%ebx, 108(%esp)
	jl	.L129
	jg	.L171
	cmpl	%ecx, 152(%esp)
	jb	.L129
.L171:
	movl	136(%esp), %eax
	movl	56(%esp), %ecx
	movl	60(%esp), %ebx
	movl	%eax, %edx
	movl	%eax, 128(%esp)
	movl	216(%esp), %eax
	sarl	$31, %edx
	addl	$1, %ecx
	adcl	$0, %ebx
	movl	%ebx, 60(%esp)
	movl	%eax, 88(%esp)
	movl	%eax, %ebx
	movl	220(%esp), %eax
	movl	%edx, 132(%esp)
	sarl	$31, %ebx
	movl	%ecx, 56(%esp)
	movl	%ebx, 92(%esp)
	movl	%eax, %edx
	movl	%eax, 96(%esp)
	movl	224(%esp), %eax
	sarl	$31, %edx
	movl	%edx, 100(%esp)
	movl	%eax, %ecx
	movl	%eax, 168(%esp)
	movl	228(%esp), %eax
	sarl	$31, %ecx
	movl	%ecx, 172(%esp)
	movl	140(%esp), %ecx
	movl	%eax, %ebx
	movl	%eax, 152(%esp)
	movl	132(%esp), %eax
	sarl	$31, %ebx
	movl	%ebx, 156(%esp)
	movl	176(%esp), %ebx
	movl	%eax, 120(%esp)
	jmp	.L158
	.p2align 4,,7
	.p2align 3
.L155:
	addl	$1, 104(%esp)
	adcl	$0, 108(%esp)
	movl	108(%esp), %eax
	movl	104(%esp), %edx
	xorl	148(%esp), %eax
	xorl	144(%esp), %edx
	orl	%edx, %eax
	je	.L129
	movl	112(%esp), %edx
	movl	140(%esp), %eax
	movl	136(%esp), %ecx
	movl	120(%esp), %ebx
	movl	%edx, 136(%esp)
	movl	%eax, 120(%esp)
.L158:
	movl	92(%esp), %eax
	movl	120(%esp), %edx
	imull	136(%esp), %eax
	imull	88(%esp), %edx
	leal	(%eax,%edx), %esi
	movl	88(%esp), %eax
	mull	136(%esp)
	addl	%esi, %edx
	movl	%eax, 64(%esp)
	movl	96(%esp), %eax
	movl	%edx, 68(%esp)
	movl	100(%esp), %edx
	imull	%ebx, %eax
	imull	%ecx, %edx
	leal	(%edx,%eax), %ebx
	movl	96(%esp), %eax
	mull	%ecx
	movl	152(%esp), %ecx
	addl	%ebx, %edx
	movl	156(%esp), %ebx
	movl	%eax, 72(%esp)
	movl	72(%esp), %eax
	movl	%edx, 76(%esp)
	movl	76(%esp), %edx
	addl	64(%esp), %eax
	adcl	68(%esp), %edx
	addl	168(%esp), %eax
	adcl	172(%esp), %edx
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	__moddi3
	movl	84(%esp), %ebx
	movl	%eax, 112(%esp)
	movl	128(%esp), %eax
	movl	%edx, 140(%esp)
	movl	132(%esp), %edx
	xorl	112(%esp), %eax
	xorl	140(%esp), %edx
	orl	%edx, %eax
	sete	%al
	xorl	%edx, %edx
	movzbl	%al, %eax
	addl	%eax, 56(%esp)
	adcl	%edx, 60(%esp)
	cmpl	%ebx, 80(%esp)
	je	.L155
	movl	80(%esp), %eax
	movl	104(%esp), %edx
	sall	$4, %eax
	movl	query+8(%eax), %edi
	movl	query+12(%eax), %esi
	movl	108(%esp), %eax
	xorl	%edi, %edx
	xorl	%esi, %eax
	orl	%edx, %eax
	jne	.L155
	movl	80(%esp), %ebx
	addl	$1, %ebx
	movl	%ebx, %ecx
	sall	$4, %ecx
	addl	$query+8, %ecx
	jmp	.L156
.L196:
	addl	$1, %ebx
.L156:
	movl	80(%esp), %eax
	movl	%ebx, 80(%esp)
	sall	$4, %eax
	movl	query(%eax), %ebp
	movl	query+4(%eax), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	movl	%eax, 176(%esp)
	movl	%edx, 68(%esp)
	movl	60(%esp), %edx
	movl	68(%esp), %eax
	imull	176(%esp), %edx
	imull	56(%esp), %eax
	addl	%edx, %eax
	movl	%eax, 64(%esp)
	movl	56(%esp), %eax
	mull	176(%esp)
	movl	%eax, 72(%esp)
	movl	64(%esp), %eax
	addl	%eax, %edx
	movl	72(%esp), %eax
	addl	%eax, ans(,%ebp,8)
	movl	%edx, 76(%esp)
	movl	76(%esp), %edx
	adcl	%edx, ans+4(,%ebp,8)
	cmpl	%ebx, 84(%esp)
	je	.L155
	addl	$16, %ecx
	movl	-12(%ecx), %eax
	movl	-16(%ecx), %edx
	xorl	%esi, %eax
	xorl	%edi, %edx
	orl	%edx, %eax
	jne	.L155
	jmp	.L196
.L151:
	movl	168(%esp), %ecx
	movl	%ebx, (%esp)
	movl	%ecx, 4(%esp)
	call	_ZSt16__insertion_sortIP5QueryEvT_S2_
	jmp	.L186
	.cfi_endproc
.LFE430:
	.size	_Z5solvev, .-_Z5solvev
	.section	.rodata.str1.1
.LC3:
	.string	"%d"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB431:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	leal	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC3, (%esp)
	call	scanf
	jmp	.L202
	.p2align 4,,7
	.p2align 3
.L203:
	call	_Z5solvev
.L202:
	movl	28(%esp), %eax
	leal	-1(%eax), %edx
	testl	%eax, %eax
	movl	%edx, 28(%esp)
	jne	.L203
	xorl	%eax, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE431:
	.size	main, .-main
	.globl	query
	.bss
	.align 32
	.type	query, @object
	.size	query, 640640
query:
	.zero	640640
	.globl	hashAcc
	.align 32
	.type	hashAcc, @object
	.size	hashAcc, 80056
hashAcc:
	.zero	80056
	.globl	hashPos
	.align 32
	.type	hashPos, @object
	.size	hashPos, 80056
hashPos:
	.zero	80056
	.globl	ans
	.align 32
	.type	ans, @object
	.size	ans, 160080
ans:
	.zero	160080
	.ident	"GCC: (Ubuntu/Linaro 4.6.1-9ubuntu3) 4.6.1"
	.section	.note.GNU-stack,"",@progbits
