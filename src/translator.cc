// --------------------------------------------------------------------------
// Datei : translator.cc
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
# include "kallup/common.h"

// TODO: translation file
std::string
lookup(std::string t) {
	class TranslatorClass *apptr = new TranslatorClass("winpermDEU");
	std::string res = apptr->lookup(t);

	if (res.size())
	return res;
	return t;
}

// default charset is UTF-8
#if defined(HAVE_ENCODING_ASCII)
Translator < Encoding_ASCII > tr;
# elif defined(HAVE_ENCODING_UTF8)
Translator < Encoding_UTF8  > tr;
# elif defined(HAVE_ENCODING_UNICODE)
Translator < Encoding_UTF8  > tr;
# elif defined(HAVE_ENCODING_UTF16)
Translator < Encoding_UTF16 > tr;
# else
# define HAVE_ENCODING_UTF8    1
# define HAVE_ENCODING_UNICODE 1
Translator< Encoding_UTF8 > tr;
#endif

TranslatorClass::TranslatorClass(std::string filename) {
    mo_data                 = nullptr;
    num_strings             = 0;
    original_table_offset   = 0;
    translated_table_offset = 0;
    hash_num_entries        = 0;
    hash_offset             = 0;

	// todo: directory stuff

	// -----------------------------------------
	// we use 3 factor search level:
	// 1: current directory of exe
	// 2: exe folder + ./loc
	// 3: mingw share folder: /mingw64/share
	// -----------------------------------------
	std::stringstream cur_file;
	char *cur_path = (char *) malloc(512);
	if (cur_path == nullptr) {
		::std::cerr << "memory error." <<
		::std::endl  ;
		exit(FAILURE);
	}

	getcwd(cur_path, 512);
	bool found = false;

	cur_file.str() = ::std::string("");
	cur_file << cur_path << "/" << filename << ".mo";
    FILE *file_handle = fopen(cur_file.str().c_str(), "rb");
	if (!file_handle)
	{
		found = false;
		cur_file.str(::std::string());
		cur_file << cur_path << "/loc/" << filename << ".mo";
		
		file_handle = fopen(cur_file.str().c_str(), "rb");
		if (!file_handle)
		{
			found = false;
			cur_file.str(::std::string());
			cur_file << "/mingw64/share/" << filename << ".mo";
			
			file_handle = fopen(cur_file.str().c_str(), "rb");
			if (!file_handle) {
				found = false;
			}	else {
				found = true;
			}
		}	else {
			found = true;
		}
	}	else {
		found = true;
	}

	if ((found == false)
	||  (!file_handle)) {
		::std::cout
			<< "could not open locale: "
			<< cur_file.str()
			<<
		::std::endl;
		
		free(cur_path);
		exit(FAILURE);
	}

    void *data;
    uint32_t length = read_file(file_handle, &data);

	// ---------------------------
	// we have our data in memory,
	// then free temporary ...
	// ---------------------------
	free(cur_path);
    fclose(file_handle);

    if (length < 0) return;
    if (length < 24) {
        abort();
        return;
    }

    mo_data = data;

    uint32_t *long_ptr = (uint32_t *)data;

    const uint32_t TARGET_MAGIC          = 0x950412DE;
    const uint32_t TARGET_MAGIC_REVERSED = 0xDE120495;
    uint32_t magic = long_ptr[0];

    if (magic == TARGET_MAGIC) {
        reversed = 0;
    } else if (magic == TARGET_MAGIC_REVERSED) {
        reversed = 1;
    } else {
        abort();
        return;
    }

    num_strings             = read_offset( 8);
    original_table_offset   = read_offset(12);
    translated_table_offset = read_offset(16);
    hash_num_entries        = read_offset(20);
    hash_offset             = read_offset(24);

    if (hash_num_entries == 0) {
        abort();
        return;
    }
}

# define HASHWORDBITS 32
static uint32_t
hashpjw(std::string str_param) {

   uint32_t hval = 0;
   uint32_t g;
   const char *s = str_param.c_str();
 
   while (*s) {
       hval <<= 4;
       hval += (unsigned char) *s++;
       g = hval & ((uint32_t) 0xf << (HASHWORDBITS - 4));
       if (g != 0) {
           hval ^= g >> (HASHWORDBITS - 8);
           hval ^= g;
       }
   }

   return hval;
}

uint32_t
TranslatorClass::read_file(FILE *file, void **data_return)
{
    assert(file);
    uint32_t descriptor = fileno(file);

    struct stat file_stats;
    uint32_t result = fstat(descriptor, &file_stats);
    if (result == -1) return -1;

    uint32_t length = file_stats.st_size;

    unsigned char *data = new unsigned char[length];

    fseek(file, 0, SEEK_SET);
    int success = fread((void *)data, length, 1, file);
    if (success < 1) {
        delete [] data;
        return -1;
    }

    *data_return = data;
    return length;
}

uint32_t
TranslatorClass::my_swap4(uint32_t result)
{
    uint32_t c0 = (result >>  0) & 0xff;
    uint32_t c1 = (result >>  8) & 0xff;
    uint32_t c2 = (result >> 16) & 0xff;
    uint32_t c3 = (result >> 24) & 0xff;

    return (c0 << 24) | (c1 << 16) | (c2 << 8) | c3;
}

uint32_t
TranslatorClass::read_offset(uint32_t offset) {
    uint32_t *ptr = (uint32_t *)(((char *)mo_data) + offset);
    
    if (reversed)
    return my_swap4(*ptr);
    return *ptr;
}

char *
TranslatorClass::src(uint32_t index)
{
    uint32_t   addr_offset = original_table_offset + 8 * index + 4;
    uint32_t string_offset = read_offset(addr_offset);

    char *t = ((char *)mo_data) + string_offset;
    return t;
}

char *
TranslatorClass::dst(uint32_t index)
{
    uint32_t   addr_offset = translated_table_offset + 8 * index + 4;
    uint32_t string_offset = read_offset(addr_offset);

    char *t = ((char *)mo_data) + string_offset;
    return t;
}

bool
TranslatorClass::matches(std::string s, uint32_t index)
{
    char *t = src(index);
    if (strcmp(s.c_str(), t) == 0)
	return true;
    return false;
}

uint32_t
TranslatorClass::dstidx(std::string s)
{
    uint32_t V = hashpjw(s);
    uint32_t S = hash_num_entries;

    uint32_t hash_cursor      = V % S;
    uint32_t orig_hash_cursor = hash_cursor;
    uint32_t increment        = 1 + (V % (S - 2));

    while (1) {
        uint32_t index = read_offset(
		hash_offset + 4 *
		hash_cursor);
		
        if (index == 0)
		break;
	
        index--;

        if (matches(s, index))
		return index;
	
        hash_cursor += increment;
        hash_cursor %= S;

        if (hash_cursor == orig_hash_cursor)
		break;
    }

    return -1;
}

void TranslatorClass::abort() {
    delete [] (char*)mo_data;
    mo_data = nullptr;
    return;
}

TranslatorClass::~TranslatorClass() {
    if (mo_data) delete [] ((char*)mo_data);
}

std::string
TranslatorClass::lookup(std::string s)
{
    if (!mo_data) {
		std::cout << "warning: data is null." <<
		std::endl ;
		return s;
	}

    int target_index = dstidx(s);
    if (target_index == -1) return s;

    return dst(target_index);
}
