; Listing generated by Microsoft (R) Optimizing Compiler Version 15.00.30729.01 

	TITLE	k:\Progs to install\My Documents\Visual Studio 2008\Projects\Intro 3D Game\Book Part III Code\Chapter 12\Camera\Camera\camera.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	??YD3DXVECTOR3@@QAEAAU0@ABU0@@Z			; D3DXVECTOR3::operator+=
PUBLIC	??0D3DXVECTOR3@@QAE@MMM@Z			; D3DXVECTOR3::D3DXVECTOR3
PUBLIC	??DD3DXVECTOR3@@QBE?AU0@M@Z			; D3DXVECTOR3::operator*
PUBLIC	??0D3DXMATRIX@@QAE@XZ				; D3DXMATRIX::D3DXMATRIX
PUBLIC	??RD3DXMATRIX@@QAEAAMII@Z			; D3DXMATRIX::operator()
PUBLIC	?D3DXVec3Dot@@YAMPBUD3DXVECTOR3@@0@Z		; D3DXVec3Dot
PUBLIC	??0D3DXVECTOR3@@QAE@XZ				; D3DXVECTOR3::D3DXVECTOR3
PUBLIC	?D3DXVec3Cross@@YAPAUD3DXVECTOR3@@PAU1@PBU1@1@Z	; D3DXVec3Cross
EXTRN	@__security_check_cookie@4:PROC
EXTRN	_D3DXMatrixRotationY@8:PROC
EXTRN	_D3DXVec3TransformCoord@12:PROC
EXTRN	_D3DXMatrixRotationAxis@12:PROC
EXTRN	_D3DXVec3Normalize@8:PROC
_CameraKeyTimeScale DD 042c80000r		; 100
PUBLIC	?setPosition@Camera@@QAEXPAUD3DXVECTOR3@@@Z	; Camera::setPosition
; Function compile flags: /Ogtpy
;	COMDAT ?setPosition@Camera@@QAEXPAUD3DXVECTOR3@@@Z
_TEXT	SEGMENT
?setPosition@Camera@@QAEXPAUD3DXVECTOR3@@@Z PROC	; Camera::setPosition, COMDAT
; _pos$ = eax
; File k:\progs to install\my documents\visual studio 2008\projects\intro 3d game\book part iii code\chapter 12\camera\camera\camera.cpp
; Line 38
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+40, ecx
	mov	edx, DWORD PTR [eax+4]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+44, edx
	mov	eax, DWORD PTR [eax+8]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+48, eax
; Line 39
	ret	0
?setPosition@Camera@@QAEXPAUD3DXVECTOR3@@@Z ENDP	; Camera::setPosition
_TEXT	ENDS
PUBLIC	??1Camera@@QAE@XZ				; Camera::~Camera
; Function compile flags: /Ogtpy
;	COMDAT ??1Camera@@QAE@XZ
_TEXT	SEGMENT
??1Camera@@QAE@XZ PROC					; Camera::~Camera, COMDAT
; Line 29
	ret	0
??1Camera@@QAE@XZ ENDP					; Camera::~Camera
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ?D3DXVec3Dot@@YAMPBUD3DXVECTOR3@@0@Z
_TEXT	SEGMENT
tv188 = -4						; size = 4
?D3DXVec3Dot@@YAMPBUD3DXVECTOR3@@0@Z PROC		; D3DXVec3Dot, COMDAT
; _pV1$ = ecx
; _pV2$ = eax
; File g:\program files\microsoft directx sdk (march 2009)\include\d3dx9math.inl
; Line 1736
	push	ecx
; Line 1742
	fld	DWORD PTR [ecx+4]
	fmul	DWORD PTR [eax+4]
	fld	DWORD PTR [ecx]
	fmul	DWORD PTR [eax]
	faddp	ST(1), ST(0)
	fld	DWORD PTR [ecx+8]
	fmul	DWORD PTR [eax+8]
	faddp	ST(1), ST(0)
	fstp	DWORD PTR tv188[esp+4]
	fld	DWORD PTR tv188[esp+4]
; Line 1743
	pop	ecx
	ret	0
?D3DXVec3Dot@@YAMPBUD3DXVECTOR3@@0@Z ENDP		; D3DXVec3Dot
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ??RD3DXMATRIX@@QAEAAMII@Z
_TEXT	SEGMENT
??RD3DXMATRIX@@QAEAAMII@Z PROC				; D3DXMATRIX::operator(), COMDAT
; _iRow$ = ecx
; _iCol$ = eax
; Line 789
	lea	eax, DWORD PTR [eax+ecx*4]
	lea	eax, DWORD PTR ?View@@3UD3DXMATRIX@@A[eax*4]
; Line 790
	ret	0
??RD3DXMATRIX@@QAEAAMII@Z ENDP				; D3DXMATRIX::operator()
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ??YD3DXVECTOR3@@QAEAAU0@ABU0@@Z
_TEXT	SEGMENT
??YD3DXVECTOR3@@QAEAAU0@ABU0@@Z PROC			; D3DXVECTOR3::operator+=, COMDAT
; _this$ = eax
; _v$ = ecx
; Line 328
	fld	DWORD PTR [ecx]
	fadd	DWORD PTR [eax]
	fstp	DWORD PTR [eax]
; Line 329
	fld	DWORD PTR [ecx+4]
	fadd	DWORD PTR [eax+4]
	fstp	DWORD PTR [eax+4]
; Line 330
	fld	DWORD PTR [ecx+8]
	fadd	DWORD PTR [eax+8]
	fstp	DWORD PTR [eax+8]
; Line 332
	ret	0
??YD3DXVECTOR3@@QAEAAU0@ABU0@@Z ENDP			; D3DXVECTOR3::operator+=
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ??0D3DXVECTOR3@@QAE@MMM@Z
_TEXT	SEGMENT
_fx$ = 8						; size = 4
_fy$ = 12						; size = 4
_fz$ = 16						; size = 4
??0D3DXVECTOR3@@QAE@MMM@Z PROC				; D3DXVECTOR3::D3DXVECTOR3, COMDAT
; _this$ = eax
; Line 304
	fld	DWORD PTR _fx$[esp-4]
	fstp	DWORD PTR [eax]
; Line 305
	fld	DWORD PTR _fy$[esp-4]
	fstp	DWORD PTR [eax+4]
; Line 306
	fld	DWORD PTR _fz$[esp-4]
	fstp	DWORD PTR [eax+8]
; Line 307
	ret	12					; 0000000cH
??0D3DXVECTOR3@@QAE@MMM@Z ENDP				; D3DXVECTOR3::D3DXVECTOR3
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ??0D3DXMATRIX@@QAE@XZ
_TEXT	SEGMENT
??0D3DXMATRIX@@QAE@XZ PROC				; D3DXMATRIX::D3DXMATRIX, COMDAT
; _this$ = eax
; File g:\program files\microsoft directx sdk (march 2009)\include\d3dx9math.h
; Line 315
	ret	0
??0D3DXMATRIX@@QAE@XZ ENDP				; D3DXMATRIX::D3DXMATRIX
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ??0D3DXVECTOR3@@QAE@XZ
_TEXT	SEGMENT
??0D3DXVECTOR3@@QAE@XZ PROC				; D3DXVECTOR3::D3DXVECTOR3, COMDAT
; _this$ = eax
; Line 165
	ret	0
??0D3DXVECTOR3@@QAE@XZ ENDP				; D3DXVECTOR3::D3DXVECTOR3
PUBLIC	?roll@Camera@@QAEXM@Z				; Camera::roll
; Function compile flags: /Ogtpy
;	COMDAT ?roll@Camera@@QAEXM@Z
_TEXT	SEGMENT
_T$74477 = -64						; size = 64
_angle$ = 8						; size = 4
?roll@Camera@@QAEXM@Z PROC				; Camera::roll, COMDAT
; File k:\progs to install\my documents\visual studio 2008\projects\intro 3d game\book part iii code\chapter 12\camera\camera\camera.cpp
; Line 126
	sub	esp, 64					; 00000040H
; Line 128
	cmp	DWORD PTR ?TheCamera@@3VCamera@@A, 1
	jne	SHORT $LN1@roll
; Line 131
	fld	DWORD PTR _angle$[esp+60]
	push	ecx
	fstp	DWORD PTR [esp]
	push	OFFSET ?TheCamera@@3VCamera@@A+28
	lea	eax, DWORD PTR _T$74477[esp+72]
	push	eax
	call	_D3DXMatrixRotationAxis@12
; Line 134
	lea	ecx, DWORD PTR _T$74477[esp+64]
	push	ecx
	push	OFFSET ?TheCamera@@3VCamera@@A+4
	push	OFFSET ?TheCamera@@3VCamera@@A+4
	call	_D3DXVec3TransformCoord@12
; Line 135
	lea	edx, DWORD PTR _T$74477[esp+64]
	push	edx
	push	OFFSET ?TheCamera@@3VCamera@@A+16
	push	OFFSET ?TheCamera@@3VCamera@@A+16
	call	_D3DXVec3TransformCoord@12
$LN1@roll:
; Line 137
	add	esp, 64					; 00000040H
	ret	4
?roll@Camera@@QAEXM@Z ENDP				; Camera::roll
_TEXT	ENDS
PUBLIC	?yaw@Camera@@QAEXM@Z				; Camera::yaw
; Function compile flags: /Ogtpy
;	COMDAT ?yaw@Camera@@QAEXM@Z
_TEXT	SEGMENT
_T$ = -64						; size = 64
_angle$ = 8						; size = 4
?yaw@Camera@@QAEXM@Z PROC				; Camera::yaw, COMDAT
; Line 109
	sub	esp, 64					; 00000040H
; Line 113
	cmp	DWORD PTR ?TheCamera@@3VCamera@@A, 0
	jne	SHORT $LN2@yaw
; Line 114
	fld	DWORD PTR _angle$[esp+60]
	push	ecx
	lea	eax, DWORD PTR _T$[esp+68]
	fstp	DWORD PTR [esp]
	push	eax
	call	_D3DXMatrixRotationY@8
$LN2@yaw:
; Line 117
	cmp	DWORD PTR ?TheCamera@@3VCamera@@A, 1
	jne	SHORT $LN1@yaw
; Line 118
	fld	DWORD PTR _angle$[esp+60]
	push	ecx
	fstp	DWORD PTR [esp]
	push	OFFSET ?TheCamera@@3VCamera@@A+16
	lea	ecx, DWORD PTR _T$[esp+72]
	push	ecx
	call	_D3DXMatrixRotationAxis@12
$LN1@yaw:
; Line 121
	lea	edx, DWORD PTR _T$[esp+64]
	push	edx
	push	OFFSET ?TheCamera@@3VCamera@@A+4
	push	OFFSET ?TheCamera@@3VCamera@@A+4
	call	_D3DXVec3TransformCoord@12
; Line 122
	lea	eax, DWORD PTR _T$[esp+64]
	push	eax
	push	OFFSET ?TheCamera@@3VCamera@@A+28
	push	OFFSET ?TheCamera@@3VCamera@@A+28
	call	_D3DXVec3TransformCoord@12
; Line 123
	add	esp, 64					; 00000040H
	ret	4
?yaw@Camera@@QAEXM@Z ENDP				; Camera::yaw
_TEXT	ENDS
PUBLIC	?pitch@Camera@@QAEXM@Z				; Camera::pitch
; Function compile flags: /Ogtpy
;	COMDAT ?pitch@Camera@@QAEXM@Z
_TEXT	SEGMENT
_T$ = -64						; size = 64
_angle$ = 8						; size = 4
?pitch@Camera@@QAEXM@Z PROC				; Camera::pitch, COMDAT
; Line 101
	fld	DWORD PTR _angle$[esp-4]
	sub	esp, 64					; 00000040H
	push	ecx
	fstp	DWORD PTR [esp]
	push	OFFSET ?TheCamera@@3VCamera@@A+4
	lea	eax, DWORD PTR _T$[esp+72]
	push	eax
	call	_D3DXMatrixRotationAxis@12
; Line 104
	lea	ecx, DWORD PTR _T$[esp+64]
	push	ecx
	push	OFFSET ?TheCamera@@3VCamera@@A+16
	push	OFFSET ?TheCamera@@3VCamera@@A+16
	call	_D3DXVec3TransformCoord@12
; Line 105
	lea	edx, DWORD PTR _T$[esp+64]
	push	edx
	push	OFFSET ?TheCamera@@3VCamera@@A+28
	push	OFFSET ?TheCamera@@3VCamera@@A+28
	call	_D3DXVec3TransformCoord@12
; Line 106
	add	esp, 64					; 00000040H
	ret	4
?pitch@Camera@@QAEXM@Z ENDP				; Camera::pitch
_TEXT	ENDS
PUBLIC	__real@c3c80000
PUBLIC	??0Camera@@QAE@W4CameraType@0@@Z		; Camera::Camera
;	COMDAT __real@c3c80000
; File g:\program files\microsoft directx sdk (march 2009)\include\d3dx9math.inl
CONST	SEGMENT
__real@c3c80000 DD 0c3c80000r			; -400
; Function compile flags: /Ogtpy
CONST	ENDS
;	COMDAT ??0Camera@@QAE@W4CameraType@0@@Z
_TEXT	SEGMENT
$T94743 = -12						; size = 12
$T94742 = -12						; size = 12
$T94741 = -12						; size = 12
$T94740 = -12						; size = 12
??0Camera@@QAE@W4CameraType@0@@Z PROC			; Camera::Camera, COMDAT
; File k:\progs to install\my documents\visual studio 2008\projects\intro 3d game\book part iii code\chapter 12\camera\camera\camera.cpp
; Line 17
	sub	esp, 12					; 0000000cH
; Line 20
	fldz
	mov	DWORD PTR ?TheCamera@@3VCamera@@A, 1
	fst	DWORD PTR $T94740[esp+12]
	mov	eax, DWORD PTR $T94740[esp+12]
	fst	DWORD PTR $T94740[esp+16]
	fld	DWORD PTR __real@c3c80000
	mov	ecx, DWORD PTR $T94740[esp+16]
	fstp	DWORD PTR $T94740[esp+20]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+40, eax
; Line 21
	fld1
	mov	edx, DWORD PTR $T94740[esp+20]
	fst	DWORD PTR $T94741[esp+12]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+48, edx
	fxch	ST(1)
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+44, ecx
	mov	eax, DWORD PTR $T94741[esp+12]
	fst	DWORD PTR $T94741[esp+16]
	fst	DWORD PTR $T94741[esp+20]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+4, eax
	mov	ecx, DWORD PTR $T94741[esp+16]
; Line 22
	fst	DWORD PTR $T94742[esp+12]
	mov	edx, DWORD PTR $T94741[esp+20]
	fst	DWORD PTR $T94742[esp+20]
	mov	eax, DWORD PTR $T94742[esp+12]
	fxch	ST(1)
	fst	DWORD PTR $T94742[esp+16]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+8, ecx
; Line 23
	fxch	ST(1)
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+12, edx
	mov	ecx, DWORD PTR $T94742[esp+16]
	fst	DWORD PTR $T94743[esp+12]
	mov	edx, DWORD PTR $T94742[esp+20]
	fstp	DWORD PTR $T94743[esp+16]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+16, eax
	mov	eax, DWORD PTR $T94743[esp+12]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+20, ecx
	mov	ecx, DWORD PTR $T94743[esp+16]
	fstp	DWORD PTR $T94743[esp+20]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+24, edx
	mov	edx, DWORD PTR $T94743[esp+20]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+28, eax
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+32, ecx
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+36, edx
; Line 24
	mov	eax, OFFSET ?TheCamera@@3VCamera@@A	; TheCamera
	add	esp, 12					; 0000000cH
	ret	0
??0Camera@@QAE@W4CameraType@0@@Z ENDP			; Camera::Camera
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ?D3DXVec3Cross@@YAPAUD3DXVECTOR3@@PAU1@PBU1@1@Z
_TEXT	SEGMENT
_v$ = -12						; size = 12
?D3DXVec3Cross@@YAPAUD3DXVECTOR3@@PAU1@PBU1@1@Z PROC	; D3DXVec3Cross, COMDAT
; _pOut$ = eax
; _pV1$ = edx
; _pV2$ = ecx
; File g:\program files\microsoft directx sdk (march 2009)\include\d3dx9math.inl
; Line 1747
	sub	esp, 12					; 0000000cH
; Line 1755
	fld	DWORD PTR [edx+4]
	fmul	DWORD PTR [ecx+8]
	fld	DWORD PTR [edx+8]
	fmul	DWORD PTR [ecx+4]
	fsubp	ST(1), ST(0)
	fstp	DWORD PTR _v$[esp+12]
; Line 1756
	fld	DWORD PTR [edx+8]
	fmul	DWORD PTR [ecx]
	fld	DWORD PTR [edx]
	fmul	DWORD PTR [ecx+8]
	fsubp	ST(1), ST(0)
	fstp	DWORD PTR _v$[esp+16]
; Line 1757
	fld	DWORD PTR [ecx+4]
	fmul	DWORD PTR [edx]
	fld	DWORD PTR [ecx]
; Line 1759
	mov	ecx, DWORD PTR _v$[esp+12]
	fmul	DWORD PTR [edx+4]
	mov	edx, DWORD PTR _v$[esp+16]
	mov	DWORD PTR [eax], ecx
	mov	DWORD PTR [eax+4], edx
	fsubp	ST(1), ST(0)
	fstp	DWORD PTR _v$[esp+20]
	mov	ecx, DWORD PTR _v$[esp+20]
	mov	DWORD PTR [eax+8], ecx
; Line 1761
	add	esp, 12					; 0000000cH
	ret	0
?D3DXVec3Cross@@YAPAUD3DXVECTOR3@@PAU1@PBU1@1@Z ENDP	; D3DXVec3Cross
; Function compile flags: /Ogtpy
_TEXT	ENDS
;	COMDAT ??DD3DXVECTOR3@@QBE?AU0@M@Z
_TEXT	SEGMENT
_f$ = 8							; size = 4
??DD3DXVECTOR3@@QBE?AU0@M@Z PROC			; D3DXVECTOR3::operator*, COMDAT
; _this$ = ecx
; ___$ReturnUdt$ = eax
; Line 393
	fld	DWORD PTR [ecx]
	fld	DWORD PTR _f$[esp-4]
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(1)
	fstp	DWORD PTR [eax]
	fld	DWORD PTR [ecx+4]
	fmul	ST(0), ST(1)
	fstp	DWORD PTR [eax+4]
	fmul	DWORD PTR [ecx+8]
	fstp	DWORD PTR [eax+8]
; Line 394
	ret	4
??DD3DXVECTOR3@@QBE?AU0@M@Z ENDP			; D3DXVECTOR3::operator*
PUBLIC	?getViewMatrix@Camera@@QAEXPAUD3DXMATRIX@@@Z	; Camera::getViewMatrix
; Function compile flags: /Ogtpy
;	COMDAT ?getViewMatrix@Camera@@QAEXPAUD3DXMATRIX@@@Z
_TEXT	SEGMENT
tv1158 = -16						; size = 4
tv1157 = -16						; size = 4
tv1156 = -16						; size = 4
_v$95036 = -12						; size = 12
_v$95024 = -12						; size = 12
?getViewMatrix@Camera@@QAEXPAUD3DXMATRIX@@@Z PROC	; Camera::getViewMatrix, COMDAT
; File k:\progs to install\my documents\visual studio 2008\projects\intro 3d game\book part iii code\chapter 12\camera\camera\camera.cpp
; Line 140
	sub	esp, 16					; 00000010H
; Line 142
	push	OFFSET ?TheCamera@@3VCamera@@A+28
	push	OFFSET ?TheCamera@@3VCamera@@A+28
	call	_D3DXVec3Normalize@8
; Line 144
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+12
	fld	ST(0)
; Line 145
	push	OFFSET ?TheCamera@@3VCamera@@A+16
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+32
	push	OFFSET ?TheCamera@@3VCamera@@A+16
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+8
	fld	ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+36
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(4)
	fsubrp	ST(1), ST(0)
	fstp	DWORD PTR _v$95024[esp+24]
	mov	eax, DWORD PTR _v$95024[esp+24]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+4
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+16, eax
	fld	ST(0)
	fmulp	ST(4), ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+28
	fld	ST(0)
	fmulp	ST(6), ST(0)
	fxch	ST(4)
	fsubrp	ST(5), ST(0)
	fxch	ST(4)
	fstp	DWORD PTR _v$95024[esp+28]
	mov	ecx, DWORD PTR _v$95024[esp+28]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+20, ecx
	fmulp	ST(2), ST(0)
	fmulp	ST(2), ST(0)
	fsubrp	ST(1), ST(0)
	fstp	DWORD PTR _v$95024[esp+32]
	mov	edx, DWORD PTR _v$95024[esp+32]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+24, edx
	call	_D3DXVec3Normalize@8
; Line 147
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+20
	fld	ST(0)
; Line 148
	push	OFFSET ?TheCamera@@3VCamera@@A+4
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+36
	push	OFFSET ?TheCamera@@3VCamera@@A+4
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+24
	fld	ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+32
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(4)
	fsubrp	ST(1), ST(0)
	fstp	DWORD PTR _v$95036[esp+24]
	mov	eax, DWORD PTR _v$95036[esp+24]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+28
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+4, eax
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+16
	fld	ST(0)
	fmulp	ST(4), ST(0)
	fxch	ST(2)
	fsubrp	ST(3), ST(0)
	fxch	ST(2)
	fstp	DWORD PTR _v$95036[esp+28]
	mov	ecx, DWORD PTR _v$95036[esp+28]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+8, ecx
	fmulp	ST(2), ST(0)
	fmulp	ST(2), ST(0)
	fsubrp	ST(1), ST(0)
	fstp	DWORD PTR _v$95036[esp+32]
	mov	edx, DWORD PTR _v$95036[esp+32]
	mov	DWORD PTR ?TheCamera@@3VCamera@@A+12, edx
	call	_D3DXVec3Normalize@8
; Line 155
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+4
	fst	DWORD PTR ?View@@3UD3DXMATRIX@@A
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+16
	fst	DWORD PTR ?View@@3UD3DXMATRIX@@A+4
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+28
	fst	DWORD PTR ?View@@3UD3DXMATRIX@@A+8
	fldz
	fst	DWORD PTR ?View@@3UD3DXMATRIX@@A+12
; Line 156
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+8
	fst	DWORD PTR ?View@@3UD3DXMATRIX@@A+16
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+20
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+20
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+32
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+24
	fxch	ST(1)
	fst	DWORD PTR ?View@@3UD3DXMATRIX@@A+28
; Line 157
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+12
	fst	DWORD PTR ?View@@3UD3DXMATRIX@@A+32
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+24
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+36
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+36
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+40
	fxch	ST(1)
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+44
; Line 158
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+40
	fld	ST(0)
	fmulp	ST(6), ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fld	ST(0)
	fmulp	ST(4), ST(0)
	fxch	ST(6)
	faddp	ST(3), ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+48
	fld	ST(0)
	fmulp	ST(3), ST(0)
	fxch	ST(3)
	faddp	ST(2), ST(0)
	fxch	ST(1)
	fstp	DWORD PTR tv1158[esp+16]
	fld	DWORD PTR tv1158[esp+16]
	fchs
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+48
	fld	ST(0)
	fmulp	ST(4), ST(0)
	fld	ST(4)
	fmul	DWORD PTR ?TheCamera@@3VCamera@@A+20
	faddp	ST(4), ST(0)
	fld	ST(1)
	fmul	DWORD PTR ?TheCamera@@3VCamera@@A+24
	faddp	ST(4), ST(0)
	fxch	ST(3)
	fstp	DWORD PTR tv1157[esp+16]
	fld	DWORD PTR tv1157[esp+16]
	fchs
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+52
	fxch	ST(2)
	fmulp	ST(1), ST(0)
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+32
	fmulp	ST(3), ST(0)
	faddp	ST(2), ST(0)
	fmul	DWORD PTR ?TheCamera@@3VCamera@@A+36
	faddp	ST(1), ST(0)
	fstp	DWORD PTR tv1156[esp+16]
	fld	DWORD PTR tv1156[esp+16]
	fchs
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+56
	fld1
	fstp	DWORD PTR ?View@@3UD3DXMATRIX@@A+60
; Line 159
	add	esp, 16					; 00000010H
	ret	0
?getViewMatrix@Camera@@QAEXPAUD3DXMATRIX@@@Z ENDP	; Camera::getViewMatrix
_TEXT	ENDS
PUBLIC	?fly@Camera@@QAEXM@Z				; Camera::fly
; Function compile flags: /Ogtpy
;	COMDAT ?fly@Camera@@QAEXM@Z
_TEXT	SEGMENT
$T95109 = -12						; size = 12
_units$ = 8						; size = 4
?fly@Camera@@QAEXM@Z PROC				; Camera::fly, COMDAT
; Line 91
	mov	eax, DWORD PTR ?TheCamera@@3VCamera@@A
	sub	esp, 12					; 0000000cH
	test	eax, eax
	jne	SHORT $LN2@fly
; Line 92
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fadd	DWORD PTR _units$[esp+8]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+44
; Line 96
	add	esp, 12					; 0000000cH
	ret	4
$LN2@fly:
; Line 94
	cmp	eax, 1
	jne	SHORT $LN9@fly
; Line 95
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+16
	fld	DWORD PTR _units$[esp+8]
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(1)
	fstp	DWORD PTR $T95109[esp+12]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+20
	fmul	ST(0), ST(1)
	fstp	DWORD PTR $T95109[esp+16]
	fmul	DWORD PTR ?TheCamera@@3VCamera@@A+24
	fstp	DWORD PTR $T95109[esp+20]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+40
	fadd	DWORD PTR $T95109[esp+12]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+40
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fadd	DWORD PTR $T95109[esp+16]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+48
	fadd	DWORD PTR $T95109[esp+20]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+48
$LN9@fly:
; Line 96
	add	esp, 12					; 0000000cH
	ret	4
?fly@Camera@@QAEXM@Z ENDP				; Camera::fly
_TEXT	ENDS
PUBLIC	__real@0000000000000000
PUBLIC	?strafe@Camera@@QAEXM@Z				; Camera::strafe
;	COMDAT __real@0000000000000000
; File g:\program files\microsoft directx sdk (march 2009)\include\d3dx9math.inl
CONST	SEGMENT
__real@0000000000000000 DQ 00000000000000000r	; 0
; Function compile flags: /Ogtpy
CONST	ENDS
;	COMDAT ?strafe@Camera@@QAEXM@Z
_TEXT	SEGMENT
$T95131 = -12						; size = 12
$T95130 = -12						; size = 12
_units$ = 8						; size = 4
?strafe@Camera@@QAEXM@Z PROC				; Camera::strafe, COMDAT
; File k:\progs to install\my documents\visual studio 2008\projects\intro 3d game\book part iii code\chapter 12\camera\camera\camera.cpp
; Line 81
	mov	eax, DWORD PTR ?TheCamera@@3VCamera@@A
	sub	esp, 12					; 0000000cH
	test	eax, eax
	jne	SHORT $LN11@strafe
; Line 82
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+4
	fld	DWORD PTR _units$[esp+8]
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(1)
	fstp	DWORD PTR $T95130[esp+12]
	fld	QWORD PTR __real@0000000000000000
	fmul	ST(0), ST(1)
; Line 84
	jmp	SHORT $LN19@strafe
; Line 82
$LN11@strafe:
; Line 84
	cmp	eax, 1
	jne	SHORT $LN17@strafe
; Line 85
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+4
	fld	DWORD PTR _units$[esp+8]
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(1)
	fstp	DWORD PTR $T95131[esp+12]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+8
	fmul	ST(0), ST(1)
$LN19@strafe:
	fstp	DWORD PTR $T95131[esp+16]
	fmul	DWORD PTR ?TheCamera@@3VCamera@@A+12
	fstp	DWORD PTR $T95131[esp+20]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+40
	fadd	DWORD PTR $T95131[esp+12]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+40
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fadd	DWORD PTR $T95131[esp+16]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+48
	fadd	DWORD PTR $T95131[esp+20]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+48
$LN17@strafe:
; Line 86
	add	esp, 12					; 0000000cH
	ret	4
?strafe@Camera@@QAEXM@Z ENDP				; Camera::strafe
_TEXT	ENDS
PUBLIC	?walk@Camera@@QAEXM@Z				; Camera::walk
; Function compile flags: /Ogtpy
;	COMDAT ?walk@Camera@@QAEXM@Z
_TEXT	SEGMENT
$T95176 = -12						; size = 12
$T95175 = -12						; size = 12
_units$ = 8						; size = 4
?walk@Camera@@QAEXM@Z PROC				; Camera::walk, COMDAT
; Line 71
	mov	eax, DWORD PTR ?TheCamera@@3VCamera@@A
	sub	esp, 12					; 0000000cH
	test	eax, eax
	jne	SHORT $LN11@walk
; Line 72
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+28
	fld	DWORD PTR _units$[esp+8]
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(1)
	fstp	DWORD PTR $T95175[esp+12]
	fld	QWORD PTR __real@0000000000000000
	fmul	ST(0), ST(1)
; Line 74
	jmp	SHORT $LN19@walk
; Line 72
$LN11@walk:
; Line 74
	cmp	eax, 1
	jne	SHORT $LN17@walk
; Line 75
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+28
	fld	DWORD PTR _units$[esp+8]
	fld	ST(0)
	fmulp	ST(2), ST(0)
	fxch	ST(1)
	fstp	DWORD PTR $T95176[esp+12]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+32
	fmul	ST(0), ST(1)
$LN19@walk:
	fstp	DWORD PTR $T95176[esp+16]
	fmul	DWORD PTR ?TheCamera@@3VCamera@@A+36
	fstp	DWORD PTR $T95176[esp+20]
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+40
	fadd	DWORD PTR $T95176[esp+12]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+40
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fadd	DWORD PTR $T95176[esp+16]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+44
	fld	DWORD PTR ?TheCamera@@3VCamera@@A+48
	fadd	DWORD PTR $T95176[esp+20]
	fstp	DWORD PTR ?TheCamera@@3VCamera@@A+48
$LN17@walk:
; Line 76
	add	esp, 12					; 0000000cH
	ret	4
?walk@Camera@@QAEXM@Z ENDP				; Camera::walk
PUBLIC	__real@c059000000000000
PUBLIC	__real@4059000000000000
PUBLIC	?ProcessKeyInput@Camera@@SA_NIPAV1@M@Z		; Camera::ProcessKeyInput
;	COMDAT __real@c059000000000000
CONST	SEGMENT
__real@c059000000000000 DQ 0c059000000000000r	; -100
CONST	ENDS
;	COMDAT __real@4059000000000000
CONST	SEGMENT
__real@4059000000000000 DQ 04059000000000000r	; 100
; Function compile flags: /Ogtpy
CONST	ENDS
;	COMDAT ?ProcessKeyInput@Camera@@SA_NIPAV1@M@Z
_TEXT	SEGMENT
_timeDelta$ = -8					; size = 4
tv187 = -4						; size = 4
tv183 = -4						; size = 4
tv180 = -4						; size = 4
tv177 = -4						; size = 4
tv174 = -4						; size = 4
tv171 = -4						; size = 4
?ProcessKeyInput@Camera@@SA_NIPAV1@M@Z PROC		; Camera::ProcessKeyInput, COMDAT
; _wParam$ = eax
; Line 167
	sub	esp, 12					; 0000000cH
	fld	DWORD PTR ?timeDelta@@3MA		; timeDelta
; Line 168
	add	eax, -37				; ffffffdbH
	fstp	DWORD PTR _timeDelta$[esp+12]
	cmp	eax, 153				; 00000099H
	ja	$LN1@ProcessKey
	movzx	eax, BYTE PTR $LN18@ProcessKey[eax]
	jmp	DWORD PTR $LN20@ProcessKey[eax*4]
$LN13@ProcessKey:
; Line 171
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fmul	QWORD PTR __real@4059000000000000
	fstp	DWORD PTR tv187[esp+16]
	fld	DWORD PTR tv187[esp+16]
	fstp	DWORD PTR [esp]
	call	?walk@Camera@@QAEXM@Z			; Camera::walk
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN12@ProcessKey:
; Line 174
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fmul	QWORD PTR __real@c059000000000000
	fstp	DWORD PTR tv183[esp+16]
	fld	DWORD PTR tv183[esp+16]
	fstp	DWORD PTR [esp]
	call	?walk@Camera@@QAEXM@Z			; Camera::walk
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN11@ProcessKey:
; Line 177
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fmul	QWORD PTR __real@c059000000000000
	fstp	DWORD PTR tv180[esp+16]
	fld	DWORD PTR tv180[esp+16]
	fstp	DWORD PTR [esp]
	call	?strafe@Camera@@QAEXM@Z			; Camera::strafe
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN10@ProcessKey:
; Line 180
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fmul	QWORD PTR __real@4059000000000000
	fstp	DWORD PTR tv177[esp+16]
	fld	DWORD PTR tv177[esp+16]
	fstp	DWORD PTR [esp]
	call	?strafe@Camera@@QAEXM@Z			; Camera::strafe
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN9@ProcessKey:
; Line 183
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fmul	QWORD PTR __real@4059000000000000
	fstp	DWORD PTR tv174[esp+16]
	fld	DWORD PTR tv174[esp+16]
	fstp	DWORD PTR [esp]
	call	?fly@Camera@@QAEXM@Z			; Camera::fly
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN8@ProcessKey:
; Line 186
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fmul	QWORD PTR __real@c059000000000000
	fstp	DWORD PTR tv171[esp+16]
	fld	DWORD PTR tv171[esp+16]
	fstp	DWORD PTR [esp]
	call	?fly@Camera@@QAEXM@Z			; Camera::fly
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN7@ProcessKey:
; Line 189
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fstp	DWORD PTR [esp]
	call	?pitch@Camera@@QAEXM@Z			; Camera::pitch
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN6@ProcessKey:
; Line 192
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fchs
	fstp	DWORD PTR [esp]
	call	?pitch@Camera@@QAEXM@Z			; Camera::pitch
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN5@ProcessKey:
; Line 195
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fchs
	fstp	DWORD PTR [esp]
	call	?yaw@Camera@@QAEXM@Z			; Camera::yaw
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN4@ProcessKey:
; Line 198
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fstp	DWORD PTR [esp]
	call	?yaw@Camera@@QAEXM@Z			; Camera::yaw
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN3@ProcessKey:
; Line 201
	fld	DWORD PTR _timeDelta$[esp+12]
; Line 204
	push	ecx
	fstp	DWORD PTR [esp]
	call	?roll@Camera@@QAEXM@Z			; Camera::roll
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN2@ProcessKey:
; Line 204
	fld	DWORD PTR _timeDelta$[esp+12]
	push	ecx
	fchs
	fstp	DWORD PTR [esp]
	call	?roll@Camera@@QAEXM@Z			; Camera::roll
; Line 209
	mov	al, 1
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
$LN1@ProcessKey:
; Line 207
	xor	al, al
; Line 210
	add	esp, 12					; 0000000cH
	ret	0
	npad	3
$LN20@ProcessKey:
	DD	$LN5@ProcessKey
	DD	$LN7@ProcessKey
	DD	$LN4@ProcessKey
	DD	$LN6@ProcessKey
	DD	$LN11@ProcessKey
	DD	$LN10@ProcessKey
	DD	$LN8@ProcessKey
	DD	$LN9@ProcessKey
	DD	$LN12@ProcessKey
	DD	$LN13@ProcessKey
	DD	$LN3@ProcessKey
	DD	$LN2@ProcessKey
	DD	$LN1@ProcessKey
$LN18@ProcessKey:
	DB	0
	DB	1
	DB	2
	DB	3
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	4
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	5
	DB	12					; 0000000cH
	DB	6
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	7
	DB	8
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	9
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	12					; 0000000cH
	DB	10					; 0000000aH
	DB	12					; 0000000cH
	DB	11					; 0000000bH
?ProcessKeyInput@Camera@@SA_NIPAV1@M@Z ENDP		; Camera::ProcessKeyInput
END
