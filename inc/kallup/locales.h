// --------------------------------------------------------------------------
// Datei : locales.h
// Autor : Jens Kallup <kallup.jens@web.de>
// Lic   : non-profit
//         (c) 2021 kallup.net - non-profit
//         Nur für Schulungszwecke !
//
// Notes : Simulations-Programm für das verteilte Rechnen von
//         rechenintensiven, mathematischer Aufgaben.
//
// Depend: keine.
// --------------------------------------------------------------------------
#pragma once
#ifndef TRANSLATOR__H
#define TRANSLATOR__H

# include "common.h"

// translation macro/inline
inline char* _tr(char *s) { return ::gettext(s); }

class TranslatorClass {
public:
     TranslatorClass(std::string);
    ~TranslatorClass();

	std::string lookup(std::string);
	
private:
    void abort();
	void *mo_data;

	uint32_t reversed;
	uint32_t num_strings;
	uint32_t original_table_offset;
	uint32_t translated_table_offset;
	uint32_t hash_num_entries;
	uint32_t hash_offset;

private:
	uint32_t my_swap4(uint32_t result);
	uint32_t read_file(FILE*,void**);
	uint32_t read_offset(uint32_t);
	char *   src(uint32_t);
	char *   dst(uint32_t);
	uint32_t srcidx (std::string);
	uint32_t dstidx (std::string);
	bool     matches(std::string,uint32_t);
};

extern std::string lookup(std::string);
extern TranslatorClass *processLocale;

class Encoding_ASCII {
	std::string internal;
public:
	Encoding_ASCII(auto key)
	: internal(key)
	{}
	auto value() {
		return ::lookup(internal);
	}
};
class Encoding_UTF8 {
	std::string internal;
public:
	Encoding_UTF8(auto key)
	: internal(key)
	{}
	auto value() {
		return ::lookup(internal);
	}
};
class Encoding_UTF16 {
	std::string internal;
public:
	Encoding_UTF16(auto key)
	: internal(key)
	{}
	auto value() {
		return ::lookup(internal);
	}
};
template<typename EncodingConverter>
struct Translator {
	auto operator()(auto key) {
		EncodingConverter converter(key);
		return converter.value();
	}
};

// default charset is UTF-8
#if    defined(HAVE_ENCODING_ASCII)
extern Translator < Encoding_ASCII > tr;
# elif defined(HAVE_ENCODING_UTF8   )
extern Translator < Encoding_UTF8  > tr;
# elif defined(HAVE_ENCODING_UNICODE)
extern Translator < Encoding_UTF8  > tr;
# elif defined(HAVE_ENCODING_UTF16  )
extern Translator < Encoding_UTF16 > tr;
#else
# define HAVE_ENCODING_UTF8    1
# define HAVE_ENCODING_UNICODE 1
  extern Translator< Encoding_UTF8 > tr;
#endif

#endif
