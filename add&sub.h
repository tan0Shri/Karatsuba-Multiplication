// Function to pad zeros to the beginning of the array
void padZero(struct number* integer, int targetLen) {
    int diff = targetLen - integer->len;
    struct number temp = makeInt(targetLen);
    memcpy(temp.num+diff,integer->num, integer->len);
    free(integer->num);
    *integer=temp;
}

// Function to make two arrays of equal length
void eqLen(struct number* num1, struct number* num2) {
    int l1=num1->len;
    int l2=num2->len;
    if (l1 < l2)
        padZero(num1,l2);
    else if (l1 > l2)
        padZero(num2,l1);
}

// Function to add two integers
struct number add(struct number* num1, struct number* num2) {
    int carry = 0;
    eqLen(num1,num2);
    int l = num1->len;
    struct number result= makeInt(l);
    for (int i = l-1; i >= 0; --i) {
        int sum = num1->num[i] + num2->num[i] + carry;
        result.num[i] = sum;
        carry = sum >> 8;
    }   
    if(carry != 0){
    	padZero(&result,l+1);
    	result.num[0]=1;
    }
    return result;
}

// Function to subtract two intgers, using 2's complement
// N.B.: For this particular interest we would always have positive resultant
struct number sub(struct number* num1, struct number* num2) {
	eqLen(num1,num2);
	int l = num1->len;
	struct number complement = makeInt(l);
	for (int i=0; i<l;++i)
		complement.num[i]= num2->num[i] ^ 0xff; // 1's complement of the subtrahend
	struct number just1 = makeInt(1);
	just1.num[0]=1;
	complement = add(&complement,&just1); // 2's complement of the subtrahend
	struct number result;
	result=add(num1,&complement);
	//Ignore the carry bit(if there is any)
    memmove(result.num, result.num + 1 , l);
    result.len--;
	//Free allocated memory
	free(just1.num);
	free(complement.num);
	return result;
}
