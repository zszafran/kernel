.global load_page_directory
.global enable_paging
.global disable_paging

load_page_directory:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    mov %eax, %cr3
    mov %ebp, %esp
    pop %ebp
    ret

enable_paging:
    push %ebp
    mov %esp, %ebp
    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0
    mov %ebp, %esp
    pop %ebp
    ret

disable_paging:
    push %ebp
    mov %esp, %ebp
    mov %cr0, %eax
    and $0x7FFFFFFF, %eax
    mov %eax, %cr0
    mov %ebp, %esp
    pop %ebp
    ret