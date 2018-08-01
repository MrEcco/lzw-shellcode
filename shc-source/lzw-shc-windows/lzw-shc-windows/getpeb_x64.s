.code
  getPEB proc
    mov     rax, gs:[60h]
	ret
  getPEB endp
  getEIP proc
    mov     rax, [rsp];
	ret
  getEIP endp
end
