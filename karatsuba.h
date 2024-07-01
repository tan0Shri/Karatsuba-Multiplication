// Function to multiply two integers
struct number karatsuba(struct number* x, struct number* y) {
    eqLen(x,y); //Make x & y of equal length
    int len = x->len;    
    // Base case: If both number is of single byte
    if(len==1){
    	struct number result= makeInt(1);
       	int product= x->num[0] * y->num[0];
       	int carry=0;
       	result.num[0] = product;
       	carry = product >> 8;
        if(carry != 0){
			padZero(&result,2);
    		result.num[0]=carry;
  	    }
    	return result;
	} else {
    	// Split the input numbers into two halves
    	int n2 = len/2;
    	struct number xL = makeInt(n2);
    	struct number xR = makeInt(len - n2);
    	struct number yL = makeInt(n2 );
    	struct number yR = makeInt(len - n2);
    	memcpy(xL.num, x->num, n2);
    	memcpy(xR.num, x->num + n2, len - n2);
    	memcpy(yL.num, y->num, n2);
    	memcpy(yR.num, y->num + n2, len - n2);
    	
    	// Perform the recursive steps
    	struct number P1 = karatsuba(&xL, &yL);
    	struct number P2 = karatsuba(&xR, &yR);
    	struct number P1P2 = add(&P1,&P2);
    	struct number xLR = add(&xL, &xR);
    	struct number yLR = add(&yL, &yR);
    	struct number P3 = karatsuba(&xLR, &yLR);
    	struct number P4 = sub(&P3,&P1P2);
    	
    	// Get the final result from P1, P2, P3, P4
    	struct number result = makeInt((2*len));
    	padZero(&P1,2*n2);
    	memcpy(result.num, P1.num, 2*n2);
    	result= add(&result,&P2);
    	int l = P4.len;
    	for (int i=0; i<len-n2; i++)
    		P4.num[l+i]=0;
    	P4.len = l+len-n2;
    	result= add(&result,&P4);
    
    // Free dynamically allocated memory
    free(xL.num);
    free(xR.num);
    free(yL.num);
    free(yR.num);
    free(P1.num);
    free(P2.num);
    free(P3.num);
    free(P4.num);
    free(P1P2.num);
    free(xLR.num);
    free(yLR.num);
    return result;
    }
}
