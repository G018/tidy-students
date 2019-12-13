int *ptr;

void not_null() {
	if (ptr != nullptr) {
		// Do something
	}
}

void is_null() {
	if (ptr == nullptr) {
		// Do something
	}
}

void compound_expr(bool other) {
	if (ptr == nullptr || other) {
		// Do something
	}
}

bool nomatch() {
	compound_expr(ptr != nullptr);
	return ptr == nullptr;
}
