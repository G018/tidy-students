double check_equal(double d1, double d2) {
	if (d1 == d2) {
		return d1;
	}
	return d2;
}

double check_less(double d1, double d2) {
	if (d1 < d2) {
		return d1;
	} 
	return d2;
}

double check_more(double d1, double d2) {
	if (d1 != d2) {
		return d1;
	} 
	return d2;

}

void useless(bool b1, bool b2){
	// Do Something with b
	int i1 = 0;
	int i2 = 10;

	if (i1 == i2){
		if (b1 != b2) {
			i1 = 1;
		}
	}
}

void use_other_places(double d1, double d2) {
	bool equal = d1 != d2;

	useless(d1 == d2, equal);
}