/*
 * This file is part of the Keyhunt distribution (https://github.com/albertobsd/keyhunt).
 * Copyright (c) 2023 albertobsd.
 * GNU GPL v3
 */

#include "Int.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <gmp.h>

#define U64STRINGSIZE 30

Int::Int() {
	mpz_init_set_ui(num, 0);
}

Int::Int(int32_t i32) {
	mpz_init_set_si(num, i32);
}

Int::Int(uint32_t u32) {
	mpz_init_set_ui(num, u32);
}

Int::Int(const Int &other) {
	mpz_init_set(num, other.num);
}

Int::Int(const char *str) {
	if (mpz_init_set_str(num, str, 0) != 0) {
		mpz_init_set_ui(num, 0);
	}
}

Int::Int(uint64_t u64) {
	char my_str_value[U64STRINGSIZE];
	snprintf(my_str_value, U64STRINGSIZE, "%llu", (unsigned long long)u64);
	mpz_init_set_str(num, my_str_value, 0);
}

Int::Int(int64_t i64) {
	char my_str_value[U64STRINGSIZE];
	snprintf(my_str_value, U64STRINGSIZE, "%lld", (long long)i64);
	mpz_init_set_str(num, my_str_value, 0);
}

// -------- Operações ----------

void Int::Add(uint64_t u64) {
	mpz_add_ui(num, num, u64);
}

void Int::Add(uint32_t u32) {
	mpz_add_ui(num, num, u32);
}

void Int::Add(const Int &a) {
	mpz_add(num, num, a.num);
}

void Int::Add(const Int &a, const Int &b) {
	mpz_add(num, a.num, b.num);
}

void Int::Sub(uint32_t u32) {
	mpz_sub_ui(num, num, u32);
}

void Int::Sub(uint64_t u64) {
	mpz_sub_ui(num, num, u64);
}

void Int::Sub(const Int &a) {
	mpz_sub(num, num, a.num);
}

void Int::Sub(const Int &a, const Int &b) {
	mpz_sub(num, a.num, b.num);
}

void Int::Mult(const Int &a) {
	mpz_mul(num, num, a.num);
}

void Int::Mult(uint64_t u64) {
	mpz_mul_ui(num, num, u64);
}

void Int::IMult(int64_t i64) {
	mpz_mul_si(num, num, i64);
}

void Int::Neg() {
	mpz_neg(num, num);
}

void Int::Abs() {
	mpz_abs(num, num);
}

// -------- Comparações ----------

bool Int::IsGreater(const Int &a) const {
	return mpz_cmp(num, a.num) > 0;
}

bool Int::IsGreaterOrEqual(const Int &a) const {
	return mpz_cmp(num, a.num) >= 0;
}

bool Int::IsLowerOrEqual(const Int &a) const {
	return mpz_cmp(num, a.num) <= 0;
}

bool Int::IsLower(const Int &a) const {
	return mpz_cmp(num, a.num) < 0;
}

bool Int::IsEqual(const Int &a) const {
	return mpz_cmp(num, a.num) == 0;
}

bool Int::IsZero() const {
	return mpz_cmp_ui(num, 0) == 0;
}

bool Int::IsOne() const {
	return mpz_cmp_ui(num, 1) == 0;
}

bool Int::IsPositive() const {
	return mpz_cmp_ui(num, 0) >= 0;
}

bool Int::IsNegative() const {
	return mpz_cmp_ui(num, 0) < 0;
}

bool Int::IsEven() const {
	return mpz_even_p(num) != 0;
}

bool Int::IsOdd() const {
	return mpz_odd_p(num) != 0;
}

// -------- Info e acesso ----------

int Int::GetSize() const {
	int r = mpz_sizeinbase(num, 2);
	return (r + 7) / 8;
}

int Int::GetBitLength() const {
	return mpz_sizeinbase(num, 2);
}

uint64_t Int::GetInt64() const {
	return mpz_get_ui(num);
}

uint32_t Int::GetInt32() const {
	return (uint32_t)mpz_get_ui(num);
}

int Int::GetBit(uint32_t n) const {
	return mpz_tstbit(num, n);
}

void Int::SetBit(uint32_t n) {
	mpz_setbit(num, n);
}

void Int::ClearBit(uint32_t n) {
	mpz_clrbit(num, n);
}

void Int::Get32Bytes(unsigned char *buff) const {
	size_t count = 0;
	memset(buff, 0, 32);
	mpz_export(buff + 32 - GetSize(), &count, 1, 1, 0, 0, num);
}

void Int::Set32Bytes(const unsigned char *buff) {
	mpz_import(num, 32, 1, 1, 0, 0, buff);
}

unsigned char Int::GetByte(int n) const {
	unsigned char buffer[32] = {0};
	size_t count = 0;
	Get32Bytes(buffer);
	if (n >= 0 && n < 32)
		return buffer[n];
	return 0;
}

char* Int::GetBase2() const {
	return mpz_get_str(NULL, 2, num);
}

char* Int::GetBase10() const {
	return mpz_get_str(NULL, 10, num);
}

char* Int::GetBase16() const {
	return mpz_get_str(NULL, 16, num);
}

void Int::SetInt64(uint64_t value) {
	mpz_set_ui(num, value);
}

void Int::SetInt32(uint32_t value) {
	mpz_set_ui(num, value);
}

void Int::Set(const Int& other) {
	mpz_set(num, other.num);
}

void Int::Set(const char *str) {
	mpz_set_str(num, str, 0);
}

void Int::SetBase10(const char *str) {
	mpz_set_str(num, str, 10);
}

void Int::SetBase16(const char *str) {
	mpz_set_str(num, str, 16);
}

Int::~Int() {
	mpz_clear(num);
}

// Copy assignment operator
Int& Int::operator=(const Int& other) {
	if (this != &other)
		mpz_set(num, other.num);
	return *this;
}

void Int::AddOne() {
	mpz_add_ui(num, num, 1);
}

void Int::ShiftL(uint32_t n) {
	mpz_mul_2exp(num, num, n);
}

void Int::Div(const Int &a, Int *mod) {
	if (mpz_cmp(num, a.num) < 0) {
		if (mod) mod->CLEAR();
		CLEAR();
		return;
	}
	if (mpz_cmp_ui(a.num, 0) == 0) {
		printf("Divide by 0!\n");
		return;
	}
	if (mpz_cmp(num, a.num) == 0) {
		if (mod) mod->CLEAR();
		mpz_set_ui(num, 1);
		return;
	}
	if (mod) {
		mpz_fdiv_qr(num, mod->num, num, a.num);
	} else {
		mpz_fdiv_q(num, num, a.num);
	}
}

void Int::CLEAR() {
	mpz_set_ui(num, 0);
}
