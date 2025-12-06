struct xorshift32{
	unsigned x;
	xorshift32(unsigned seed=2463534242){x=seed;}
	unsigned random(){
		x^=x<<13;
		x^=x>>17;
		return x^=x<<5;
	}
};
