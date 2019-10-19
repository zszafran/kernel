.text
.global cpu_idle
.type cpu_idle, @function
cpu_idle:
	hlt
	nop
	ret