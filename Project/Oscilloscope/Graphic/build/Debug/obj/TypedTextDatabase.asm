; Listing generated by Microsoft (R) Optimizing Compiler Version 19.28.29914.0 

	TITLE	D:\Oscilloscope\Project\Oscilloscope\Graphic\build\Debug\obj\TypedTextDatabase.obj
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

msvcjmc	SEGMENT
__C6E4F19F_Types@hpp DB 01H
__4268A301_Unicode@hpp DB 01H
__01751C5A_Font@hpp DB 01H
__0A3534CD_ConstFont@hpp DB 01H
__6FF8A0AC_InternalFlashFont@hpp DB 01H
__A08B9D52_Texts@hpp DB 01H
__15F508DE_TypedText@hpp DB 01H
__AD567E38_TypedTextDatabase@cpp DB 01H
msvcjmc	ENDS
CONST	SEGMENT
?typedText_database_DEFAULT@@3QBUTypedTextData@TypedText@touchgfx@@B DB 00H ; typedText_database_DEFAULT
	DB	01H
	DB	00H
	DB	01H
	DB	02H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	02H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	02H
	DB	01H
	DB	00H
	DB	01H
	DB	03H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	03H
	DB	01H
	DB	03H
	DB	01H
	DB	03H
	DB	01H
	DB	03H
	DB	01H
	DB	03H
	DB	01H
	DB	03H
	DB	01H
	DB	03H
	DB	01H
	DB	03H
	DB	01H
	ORG $+2
?typedTextDatabaseArray@@3QBQBUTypedTextData@TypedText@touchgfx@@B DD FLAT:?typedText_database_DEFAULT@@3QBUTypedTextData@TypedText@touchgfx@@B ; typedTextDatabaseArray
CONST	ENDS
PUBLIC	?getInstance@TypedTextDatabase@@YAPBUTypedTextData@TypedText@touchgfx@@G@Z ; TypedTextDatabase::getInstance
PUBLIC	?getFonts@TypedTextDatabase@@YAPBQBVFont@touchgfx@@XZ ; TypedTextDatabase::getFonts
PUBLIC	?getInstanceSize@TypedTextDatabase@@YAGXZ	; TypedTextDatabase::getInstanceSize
PUBLIC	__JustMyCode_Default
EXTRN	?getFont_Asap_Regular_18_4bpp@@YAAAVInternalFlashFont@touchgfx@@XZ:PROC ; getFont_Asap_Regular_18_4bpp
EXTRN	?getFont_Asap_Regular_12_4bpp@@YAAAVInternalFlashFont@touchgfx@@XZ:PROC ; getFont_Asap_Regular_12_4bpp
EXTRN	?getFont_Asap_Regular_14_8bpp@@YAAAVInternalFlashFont@touchgfx@@XZ:PROC ; getFont_Asap_Regular_14_8bpp
EXTRN	?getFont_Asap_Regular_13_4bpp@@YAAAVInternalFlashFont@touchgfx@@XZ:PROC ; getFont_Asap_Regular_13_4bpp
EXTRN	@__CheckForDebuggerJustMyCode@4:PROC
EXTRN	__RTC_CheckEsp:PROC
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
_BSS	SEGMENT
?_fonts@@3QBQBVFont@touchgfx@@B DD 04H DUP (?)		; _fonts
_BSS	ENDS
CRT$XCU	SEGMENT
?_fonts$initializer$@@3P6AXXZA DD FLAT:??__E_fonts@@YAXXZ ; _fonts$initializer$
CRT$XCU	ENDS
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
; Function compile flags: /Odt
;	COMDAT __JustMyCode_Default
_TEXT	SEGMENT
__JustMyCode_Default PROC				; COMDAT
	push	ebp
	mov	ebp, esp
	pop	ebp
	ret	0
__JustMyCode_Default ENDP
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ??__E_fonts@@YAXXZ
text$di	SEGMENT
??__E_fonts@@YAXXZ PROC					; `dynamic initializer for '_fonts'', COMDAT
; File D:\Oscilloscope\Project\Oscilloscope\Graphic\generated\texts\src\TypedTextDatabase.cpp
; Line 22
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __AD567E38_TypedTextDatabase@cpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 18
	call	?getFont_Asap_Regular_18_4bpp@@YAAAVInternalFlashFont@touchgfx@@XZ ; getFont_Asap_Regular_18_4bpp
	mov	DWORD PTR ?_fonts@@3QBQBVFont@touchgfx@@B, eax
; Line 19
	call	?getFont_Asap_Regular_12_4bpp@@YAAAVInternalFlashFont@touchgfx@@XZ ; getFont_Asap_Regular_12_4bpp
	mov	DWORD PTR ?_fonts@@3QBQBVFont@touchgfx@@B+4, eax
; Line 20
	call	?getFont_Asap_Regular_14_8bpp@@YAAAVInternalFlashFont@touchgfx@@XZ ; getFont_Asap_Regular_14_8bpp
	mov	DWORD PTR ?_fonts@@3QBQBVFont@touchgfx@@B+8, eax
; Line 21
	call	?getFont_Asap_Regular_13_4bpp@@YAAAVInternalFlashFont@touchgfx@@XZ ; getFont_Asap_Regular_13_4bpp
	mov	DWORD PTR ?_fonts@@3QBQBVFont@touchgfx@@B+12, eax
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
??__E_fonts@@YAXXZ ENDP					; `dynamic initializer for '_fonts''
text$di	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getInstanceSize@TypedTextDatabase@@YAGXZ
_TEXT	SEGMENT
?getInstanceSize@TypedTextDatabase@@YAGXZ PROC		; TypedTextDatabase::getInstanceSize, COMDAT
; File D:\Oscilloscope\Project\Oscilloscope\Graphic\generated\texts\src\TypedTextDatabase.cpp
; Line 88
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __AD567E38_TypedTextDatabase@cpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 89
	mov	eax, 45					; 0000002dH
; Line 90
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getInstanceSize@TypedTextDatabase@@YAGXZ ENDP		; TypedTextDatabase::getInstanceSize
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getFonts@TypedTextDatabase@@YAPBQBVFont@touchgfx@@XZ
_TEXT	SEGMENT
?getFonts@TypedTextDatabase@@YAPBQBVFont@touchgfx@@XZ PROC ; TypedTextDatabase::getFonts, COMDAT
; File D:\Oscilloscope\Project\Oscilloscope\Graphic\generated\texts\src\TypedTextDatabase.cpp
; Line 92
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __AD567E38_TypedTextDatabase@cpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 93
	mov	eax, OFFSET ?_fonts@@3QBQBVFont@touchgfx@@B
; Line 94
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getFonts@TypedTextDatabase@@YAPBQBVFont@touchgfx@@XZ ENDP ; TypedTextDatabase::getFonts
_TEXT	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
;	COMDAT ?getInstance@TypedTextDatabase@@YAPBUTypedTextData@TypedText@touchgfx@@G@Z
_TEXT	SEGMENT
_id$ = 8						; size = 2
?getInstance@TypedTextDatabase@@YAPBUTypedTextData@TypedText@touchgfx@@G@Z PROC ; TypedTextDatabase::getInstance, COMDAT
; File D:\Oscilloscope\Project\Oscilloscope\Graphic\generated\texts\src\TypedTextDatabase.cpp
; Line 83
	push	ebp
	mov	ebp, esp
	sub	esp, 192				; 000000c0H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-192]
	mov	ecx, 48					; 00000030H
	mov	eax, -858993460				; ccccccccH
	rep stosd
	mov	ecx, OFFSET __AD567E38_TypedTextDatabase@cpp
	call	@__CheckForDebuggerJustMyCode@4
; Line 84
	movzx	eax, WORD PTR _id$[ebp]
	mov	eax, DWORD PTR ?typedTextDatabaseArray@@3QBQBUTypedTextData@TypedText@touchgfx@@B[eax*4]
; Line 85
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 192				; 000000c0H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?getInstance@TypedTextDatabase@@YAPBUTypedTextData@TypedText@touchgfx@@G@Z ENDP ; TypedTextDatabase::getInstance
_TEXT	ENDS
END
