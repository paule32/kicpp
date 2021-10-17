// ------------------------------------------------------------------
// file:   testjit.cc
// desc:   example file for creating executeable's for Windows 10 Pro.
//         with the AsmJit by:
//         available under:
//
// autor:  Jens Kallup - <kallup.jens@web.de>
//         kallup.net * non-profit
// date:   2021-10-12
//
// policy: only for education usage !!! - no commercial use allowed.
//         free to distribute if copyright notice is intact.
// ------------------------------------------------------------------
# include "kallup/common.h"
# include "kallup/version.h"

# include <boost/program_options.hpp>
# include <asmjit/x86.h>

using namespace std;
using namespace asmjit;

namespace po = boost::program_options;	// boost: 1.77.0

// ---------------------------------------------
// used locale for the started process:
// ---------------------------------------------
class TranslatorClass *processLocale = nullptr;

// ------------------------------------------
// just a namespace, to avoid other library
// cross overs:
// ------------------------------------------
namespace kallup
{
// -------------------------------------------------
// this structures holds the options:
// legende:
//
// .F.  = false
// .T.  = true
// .S.  = string
// .I.  = int
// .D.  = float/double
// .E.  = enum class
// -------------------------------------------------
enum class ArchTypeList {
	arch_16Bit = 1,
	arch_32Bit = 2,
	arch_64Bit = 3
};
ArchTypeList ArchType = ArchTypeList::arch_32Bit;	// default
enum class PlatformList {
	os_dos16 = 1,			   // MS-DOS native 16-Bit
	os_dos32 = 2,			   // FreeDos 32-Bit
	os_win16 = 3,			   // Windows 3.11 16-Bit
	os_win32 = 4,			   // Windows      32-Bit
	os_win64 = 5,			   // Windows      64-Bit
};
PlatformList PlatformType = PlatformList::os_win32; // default
enum class OutputFormatList {
	format_coff = 1,           // output format = coff
	format_fpc  = 2,           // fpc
	format_cpp  = 3,           // gnu cpp
	format_asm  = 4            // assembler
};
OutputFormatList OutputFormat = OutputFormatList::format_coff;

struct ProgramOptions {
	PlatformList     platform  ;  // 1= DOS, 3= win16, 4= win32
	ArchTypeList     arch      ;  // 1= 16bit, 2= 32bit, 3= 64bit
	bool             hasConsole;  // started from console | desktop ?
	::std::wstring   appLocale ;  // default: en-US
	OutputFormatList outFormat ;
};
ProgramOptions appOption;

bool app_has_error = false;       // true, when error occur.

// ------------------------------------------------------------
// only english, and german locale are supported at the moment
// ------------------------------------------------------------
::std::map<::std::wstring, ::std::wstring> availLocales = {
	{ L"de-DE", L"DEU" },
	{ L"en-US", L"ENG" }
};

class kFileSections {
public:
	class header {
	public:
	};

	class code {
	public:
	};
	class data {
	public:
	};
	class init {
	public:
	};
};

// --------------------------------------
// DOS image:
// --------------------------------------
class kDOS: public kFileSections {
public:
};

// --------------------------------------
// DOS header + PE image:
// --------------------------------------
class kPE: public kFileSections {
public:
};

// --------------------------------------
// base of all supported code holders:
// --------------------------------------
class kCodeBase {
	::asmjit::Environment env;
	::asmjit::JitRuntime  run;
	::asmjit::CodeHolder  src;
public:
	kCodeBase(uint32_t arch) {
		src.init(run.environment());
	}
	~kCodeBase() {
	}
};

// Windows 10
class k64Bit: public kCodeBase {
public:
	k64Bit()
	: kCodeBase(::asmjit::Environment::kArchX64)
	{ }
};

// Windows XP
class k32Bit: public kCodeBase {
public:
	k32Bit()
	: kCodeBase(::asmjit::Environment::kArchX86)
	{ }
};

// Windows 3.11 or DOS
class k16Bit: public kCodeBase {
public:
	k16Bit(const k16Bit& r)
	: kCodeBase(::asmjit::Environment::kArchX86)
	{ }
};

class kCOFF2 {
public:
};

// --------------------------------------
// to minimize code, we use a templatee:
// --------------------------------------
class kBuildExec {
	class k16Bit* src_16 = nullptr;
	class k16Bit* dst_16 = nullptr; class kCOFF2* out_16 = nullptr;
	class k32Bit* src_32 = nullptr;
	class k32Bit* dst_32 = nullptr; class kCOFF2* out_32 = nullptr;
	class k64Bit* src_64 = nullptr;
	class k64Bit* dst_64 = nullptr; class kCOFF2* out_64 = nullptr;
public:
	kBuildExec(k16Bit* src, k16Bit *dst, kCOFF2 *out)
	: src_16(src)
	, dst_16(dst)
	, out_16(out) {
		// todo
	}
	
	kBuildExec(k16Bit* src, k32Bit* dst, kCOFF2* out)
	: src_16(src)
	, dst_32(dst)
	, out_32(out) {
		// todo
	}
	
	kBuildExec(k32Bit* src, k16Bit* dst, kCOFF2* out)
	: src_32(src)
	, dst_16(dst)
	, out_16(out) {
		// todo
	}
	
	kBuildExec(k32Bit* src, k32Bit* dst, kCOFF2* out)
	: src_32(src)
	, dst_32(dst)
	, out_32(out) {
		std::cout << typeid(src).name();
	}

	kBuildExec(k32Bit* src, k64Bit* dst, kCOFF2* out)
	: src_32(src)
	, dst_64(dst)
	, out_64(out) {
		// todo
	}

	kBuildExec(k64Bit* src, k32Bit* dst, kCOFF2* out)
	: src_64(src)
	, dst_32(dst)
	, out_32(out) {
		// todo
	}

	kBuildExec(k64Bit* src, k64Bit* dst, kCOFF2* out)
	: src_64(src)
	, dst_64(dst)
	, out_64(out) {
		// todo
	}
};	// class: kBuildExec

// --------------------------------------------
// inConsole: check if the application started
//            from a console or desktop.
// @result:   bool: true/false
// --------------------------------------------
bool inConsole()
{
	#if defined(__MINGW32__) || defined(__MINGW64__)
	HWND  conWindowID = GetConsoleWindow();
	DWORD processID;

	GetWindowThreadProcessId(conWindowID, &processID);
	if (GetCurrentProcessId() == processID)
		appOption.hasConsole   = true ; else
		appOption.hasConsole   = false;
	
	// sanity check:
	if ((appOption.hasConsole   == true)
	&&  (isatty(fileno(stdout)) == true))
		return true ; else
		return false;
	#else
		appOption.hasConsole   = true ;
	#endif
	return appOption.hasConsole;
}

void handle_signal(int signal)
{
	switch (signal) {
	#if defined(__MINGW32__) || defined(__MINGW64__)
	case SIGTERM:
	case SIGABRT:
	case SIGBREAK:
	#else
	case SIGHUP:
	#endif
		::std::cout << "on sig" << ::std::endl;
		//got_sighup = true;
		break;
	case SIGINT:
		::std::cout << "on sig iner" << ::std::endl;
		//got_sigint = true;
		break;
	}
}

#if defined(__MINGW32__) || defined(__MINGW64__)
LONG WINAPI
TopLevelExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	std::stringstream s;
	s	<< "Fatal: Unhandled exception:"
		<<
	::std::endl
		<< "code: 0x"
		<<
	::std::hex
		<< pExceptionInfo->ExceptionRecord->ExceptionCode
		<<
	::std::endl
		<< "flags: 0x"
		<<
	::std::hex
		<< pExceptionInfo->ExceptionRecord->ExceptionFlags
		<<
	::std::endl
		<< "address: "
		<<
	::std::hex
		<< pExceptionInfo->ExceptionRecord->ExceptionAddress
		<<
	::std::endl
		<< "parameter: 0x"
		<<
	::std::hex
		<< pExceptionInfo->ExceptionRecord->NumberParameters
		<<
	::std::endl;

	MessageBoxA(NULL, s.str().c_str(), "my application", MB_OK | MB_ICONSTOP);
	exit(FAILURE);

	return EXCEPTION_CONTINUE_SEARCH;
}
#endif

void init_signals()
{
	static uint8_t already_hooked = 0;
	if (already_hooked > 0) {
		return;
	}
	already_hooked = 1;
	#if defined(__MINGW32__) || defined(__MINGW64__)
		signal (SIGINT , handle_signal);
		signal (SIGTERM, handle_signal);
		signal (SIGABRT, handle_signal);
	#else
		struct sigaction sa;

		sa.sa_handler = &handle_signal;
		sa.sa_flags   = SA_RESTART;
		sigfillset(&sa.sa_mask);

		if (sigaction(SIGHUP, &sa, NULL) == -1) {
			::std::cerr
				<< "could not install SIGHUP handler."
				<<
			::std::endl;
		}
		if (sigaction(SIGINT, &sa, NULL) == -1) {
			::std::cerr
				<< "could not install SIGINT handler."
				<<
			::std::endl;
		}
	#endif
}
void destroy_signals()
{
	#if defined(__MINGW32__) || defined(__MINGW64__)
		signal(SIGINT , SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		signal(SIGABRT, SIG_DFL);
	#else
		struct sigaction sa;
	
		sa.sa_handler = SIG_DFL;
		sa.sa_flags   = SA_RESTART;
		
		sigfillset(&sa.sa_mask);

		if (sigaction(SIGHUP, &sa, NULL) == -1) {
			::std::cerr
				<< "could not un-install SIGHUP handler."
				<<
			::std::endl;
		}
		if (sigaction(SIGINT, &sa, NULL) == -1) {
			::std::cerr
				<< "could not un-install SIGINT handler."
				<<
			::std::endl;
		}
	#endif
}

// little helpers :)
void setError(bool flag) { app_has_error = flag; }
bool getError()          { return app_has_error; }

};	// namespace: kallup

::std::string copyright()
{
	::std::stringstream o;
	o	<< "jittest.exe version 1.0"                        << ::std::endl
		<< "Copyright (c) 2021 by Jens Kallup - non-profit" << ::std::endl
		<< "all rights reserved."                           << ::std::endl;
	return o.str();
}
		
// --------------------------------------
// main: application entry point ...
// --------------------------------------
int main(int argc, char **argv)
{
	try {
		// the mother of all ...
		#if defined(__MINGW32__) || defined(__MINGW64__)
		SetUnhandledExceptionFilter(
		::kallup::TopLevelExceptionHandler);
		#else
		::kallup::init_signals();
		#endif

		// ----------------------------------------------
		// first, we check the locale, and prepare the
		// translator file. default is english utf-8 ...
		// ----------------------------------------------
		#if defined(__MINGW32__) || defined(__MINGW64__)
		{
			constexpr int BUFFER_SIZE = 512;
			WCHAR  buffer[BUFFER_SIZE];
			::std::wstringstream  str1;
			::std::wstringstream  str2;
			
			int result = GetSystemDefaultLocaleName(buffer, BUFFER_SIZE);
			if (!result) {
				str1 << L"Could not get system default locale," << ::std::endl
					 << L"I use the default: English."          << ::std::endl ;
				str2 << "User-Information";
				if (::kallup::inConsole() == false) {
					::MessageBoxW(
						HWND(GetDesktopWindow()),
						LPCWSTR(str1.str().c_str()),
						LPCWSTR(str2.str().c_str()),
						UINT(MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL));
				}	else {
					::std::wcout << str1.str() <<
					::std::endl;
				}
				::kallup::appOption.appLocale = L"en-US"; } else {
				::kallup::appOption.appLocale = buffer;
			}
		}
		#endif
		
		if (argc < 2) {
			if (isatty(fileno(stdout))) {
				::std::cout
					<< copyright()
					<<
				::std::endl;
			}
		}

		// ----------------------------------------------
		// set default locale file:
		// ----------------------------------------------
		processLocale = new TranslatorClass("server");

		// ----------------------------------------------
		// locale, cert are ok, then check the arguments
		// of the application.
		// override standard options, and check again.
		// ----------------------------------------------
		po::options_description general("General options");
		using strings = ::std::vector<::std::string>;
		general.add_options()
			("help,h", po::value<::std::vector<::std::string>>()
				->multitoken()
				->implicit_value(
				strings {
					"","format","server","client","verbose","version" },
					""//,format,server,client,verbose,version"
				),
				"shows help for topic 'arg'")
			("verbose,v", po::value<::std::vector<::std::string>>()
				->multitoken()
				->implicit_value(
				strings {
					"","info","warn","error" },
					""//,info,warn,error"
				),
				"help for verbose levels.")
			("version,d", "output the version number")
		;

		po::options_description format("Format options");
		format.add_options()
			("format,f", po::value<::std::vector<::std::string>>()
				->multitoken()
				->implicit_value(
				strings { "", "coff", "fpc", "cpp", "asm" },
						  ""//,coff,fpc,cpp,asm"
				),
				"output format options.")
		;

		po::options_description arch("Platform/Arch options");
		arch.add_options()
			("platform,p", po::value<::std::vector<::std::string>>()
				->multitoken()
				->implicit_value(
					strings {
						"",
						"dos16", "dos32",
						"win16", "win32", "win64"
					},
						""//,"
						//"dos16,dos32,"
						//"win16,win32,win64"
				),
				"set platform type.")
			("arch,m", po::value<::std::vector<::std::string>>()
				->multitoken()
				->implicit_value(strings {
					"","16","32","64" },
					""//,16,32,64"
				),
				"set platform arch.")
		;
		
		po::options_description server("Server/Client options");
		server.add_options()
			("server,s", po::value<::std::vector<::std::string>>()
				->multitoken()
				->implicit_value(strings {
					"","addr","port","user","pass","cert" },
					""//,addr,port,user,pass,cert"
				),
				"server options.")
			("client,c", po::value<::std::vector<::std::string>>()
				->multitoken()
				->implicit_value(strings {
					"","addr","port","user","pass","cert" },
					""//,addr,port,user,pass,cert"
				),
				"client options.")
		;

		po::options_description all("Allowed options");
		all	.add(general)
			.add(format)
			.add(arch)
			.add(server);
		
		po::options_description visible("Allowed Options");
		visible
			.add(general)
			.add(arch)
			.add(server);

		// --------------------------------------
		// before we output on console, we check
		// if a argument is already given:
		// --------------------------------------
		if (argc < 2) {
			::std::stringstream t;
			t	<< copyright()
				<<
			::std::endl
				<< visible
				<<
			::std::endl;
			#if defined(__MINGW32__) || defined(__MINGW64__)
			if (!isatty(fileno(stdout))) {
				::MessageBoxA(
					HWND(GetDesktopWindow()),
					LPCSTR(t.str().c_str()),
					LPCSTR("User-Information") ,
					UINT(MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL));
			}	else {
			#endif
			::std::cout << t.str() <<
			::std::endl ;
			#if defined(__MINGW32__) || defined(__MINGW64__)
			}
			#endif
			return SUCCESS;
		}

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, all), vm);
		po::notify(vm);

		if (vm.count("help")) {
			::std::vector<::std::string> s = vm["help"].as<strings>();
			::std::stringstream t;
			
			if (s.at(0) == "") {
				t.str(::std::string());
				t	<< copyright()
					<<
				::std::endl
					<< "available help topics:"
					<< "\n\tformat  \toutput format options"
					<< "\n\tserver  \tserver options"
					<< "\n\tclient  \tclient options"
					<< "\n\tverbose \tverbose options"
					<<
				::std::endl;
				#if defined(__MINGW32__) || defined(__MINGW64__)
				if (!isatty(fileno(stdout))) {
					::MessageBoxA(
						HWND(GetDesktopWindow()),
						LPCSTR(t.str().c_str()),
						LPCSTR("User-Information") ,
						UINT(MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL));
				}	else {
				#endif
				::std::cout << t.str() <<
				::std::endl ;
				#if defined(__MINGW32__) || defined(__MINGW64__)
				}
				#endif
				return SUCCESS;
			}
				
			// ----------------------
			// output format options:
			// ----------------------
			else if (s.at(0) == "format" )
			{
				t.str(::std::string());
				::kallup::setError(false);
				
				if (s.size() == 2)
				{
					::std::string s2 = s.at(1);
					if (s2.empty()) {
						::kallup::setError(true);
						t	<< copyright()
							<<
						::std::endl
							<< "No output format given !"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "coff")) {
						t	<< copyright()
							<<
						::std::endl
							<< "output format coff:"
							<< "\n\tproduce MS-Windows .coff object file."
							<< "\n\tthis file can be linked to .exe or .dll"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "fpc")) {
						t	<< copyright()
							<<
						::std::endl
							<< "output format fpc:"
							<< "\n\tProduce Free Pascal Compiler (FPC) file."
							<< "\n\tThis file can be compiled with fpc.exe"
							<< "\n\tFor GUI development, you can use Lazarus."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "cpp")) {
						t	<< copyright()
							<<
						::std::endl
							<< "output format cpp:"
							<< "\n\tProduce GNU C++ Compiler (g++) file."
							<< "\n\tThis file can be compiled with g++.exe"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "asm")) {
						t	<< copyright()
							<<
						::std::endl
							<< "output format asm:"
							<< "\n\tProduce Assembler file that is compatible with NASM"
							<< "\n\tThis file can be compiled with nasm.exe to binary."
							<< "\n\tSupports various binary formats."
							<<
						::std::endl;
					}	else {
						t.str(::std::string());
						t	<< copyright()
							<<
						::std::endl
							<< "Unknown help option"
							<<
						::std::endl;
					}
				}	else {
					t	<< copyright()
						<<
					::std::endl
						<< "output format:"
						<< "\n\tcoff\tMs-Windows object file .coff"
						<< "\n\tfpc \tFPC - Pascal"
						<< "\n\tcpp \tGNU C Compiler"
						<< "\n\tasm \tNet wide assembler nasm."
						<<
					::std::endl;
				}
			}
			
			// ----------------------
			// server help options:
			// ----------------------
			else if (s.at(0) == "server" )
			{
				t.str(::std::string());
				::kallup::setError(false);
				
				if (s.size() == 2)
				{
					::std::string s2 = s.at(1);
					if (s2.empty()) {
						::kallup::setError(true);
						t	<< copyright()
							<<
						::std::endl
							<< "No server option given !"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "addr")) {
						t	<< copyright()
							<<
						::std::endl
							<< "server option 'addr':"
							<< "\n\tset the server connection address."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "port")) {
						t	<< copyright()
							<<
						::std::endl
							<< "server option 'port':"
							<< "\n\tset server connection port."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "user")) {
						t	<< copyright()
							<<
						::std::endl
							<< "server option 'user':"
							<< "\n\tset server login id."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "pass")) {
						t	<< copyright()
							<<
						::std::endl
							<< "server option 'addr':"
							<< "\n\tset server login password."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "cert")) {
						t	<< copyright()
							<<
						::std::endl
							<< "server option 'cert':"
							<< "\n\tset server certificate."
							<<
						::std::endl;
					}	else {
						t.str(::std::string());
						t	<< copyright()
							<<
						::std::endl
							<< "Unknown help option"
							<<
						::std::endl;
					}
				}	else {
					t	<< copyright()
						<<
					::std::endl
						<< "server options:"
						<< "\n\taddr\tserver connecton ip address"
						<< "\n\tport\tconnecton port"
						<< "\n\tuser\tlogin user id"
						<< "\n\tpass\tlogin user password"
						<< "\n\tcert\tlogin user certificate"
						<<
					::std::endl;
				}
			}
			
			// ----------------------
			// client help options:
			// ----------------------
			else if (s.at(0) == "client" )
			{
				t.str(::std::string());
				::kallup::setError(false);
				
				if (s.size() == 2)
				{
					::std::string s2 = s.at(1);
					if (s2.empty()) {
						::kallup::setError(true);
						t	<< copyright()
							<<
						::std::endl
							<< "No client option given !"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "addr")) {
						t	<< copyright()
							<<
						::std::endl
							<< "client option 'addr':"
							<< "\n\tset the client connection address."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "port")) {
						t	<< copyright()
							<<
						::std::endl
							<< "client option 'port':"
							<< "\n\tset client connection port."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "user")) {
						t	<< copyright()
							<<
						::std::endl
							<< "client option 'user':"
							<< "\n\tset client login id."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "pass")) {
						t	<< copyright()
							<<
						::std::endl
							<< "client option 'pass':"
							<< "\n\tset client login password."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "cert")) {
						t	<< copyright()
							<<
						::std::endl
							<< "client option 'cert':"
							<< "\n\tset client certificate."
							<<
						::std::endl;
					}	else {
						t.str(::std::string());
						t	<< copyright()
							<<
						::std::endl
							<< "Unknown help option"
							<<
						::std::endl;
					}
				}	else {
					t	<< copyright()
						<<
					::std::endl
						<< "client options:"
						<< "\n\taddr\tconnecton ip address"
						<< "\n\tport\tconnecton port"
						<< "\n\tuser\tlogin user id"
						<< "\n\tpass\tlogin user password"
						<< "\n\tcert\tlogin user certificate"
						<<
					::std::endl;
				}
			}
			
			// ----------------------
			// verbose help options:
			// ----------------------
			else if (s.at(0) == "verbose") {
				t.str(::std::string());
				::kallup::setError(false);
				
				if (s.size() == 2)
				{
					::std::string s2 = s.at(1);
					if (s2.empty()) {
						::kallup::setError(true);
						t	<< copyright()
							<<
						::std::endl
							<< "No verbose option given !"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "info")) {
						t	<< copyright()
							<<
						::std::endl
							<< "verbose option 'info':"
							<< "\n\tset verbose to display information."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "warn")) {
						t	<< copyright()
							<<
						::std::endl
							<< "set verbose option 'warn':"
							<< "\n\tset verbose to display warnings."
							<< "\n\tthis implied 'info'."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "error")) {
						t	<< copyright()
							<<
						::std::endl
							<< "set verbose option 'error':"
							<< "\n\tset verbos to display erros."
							<< "\n\tthis implieds 'info', and 'warn'."
							<<
						::std::endl;
					}	else {
						t.str(::std::string());
						t	<< copyright()
							<<
						::std::endl
							<< "Unknown help option"
							<<
						::std::endl;
					}
				}	else {
					t	<< copyright()
						<<
					::std::endl
						<< "verbose level:"
						<< "\n\tINFO  \tdisplay informations only."
						<< "\n\tWARN  \tdisplay informations, and warnings."
						<< "\n\tERROR \tdisplay error's."
						<<
					::std::endl;
				}
			}
			
			// ----------------------
			// platform help options:
			// ----------------------
			else if (s.at(0) == "platform") {
				t.str(::std::string());
				::kallup::setError(false);
				
				if (s.size() == 2)
				{
					::std::string s2 = s.at(1);
					if (s2.empty()) {
						::kallup::setError(true);
						t	<< copyright()
							<<
						::std::endl
							<< "No verbose option given !"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "dos16")) {
						t	<< copyright()
							<<
						::std::endl
							<< "set platform to 'dos16':"
							<< "\n\tnative MS-DOS 16-Bit platform (OS)"
							<< "\n\tfor MZ exec."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "dos32")) {
						t	<< copyright()
							<<
						::std::endl
							<< "set platform to 'dos32':"
							<< "\n\tnative FreeDos 32-Bit platform (OS)"
							<< "\n\tfor MZ exec."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "win16")) {
						t	<< copyright()
							<<
						::std::endl
							<< "set platform to 'win16':"
							<< "\n\tnative MS-Windows 3.11 platform (OS)"
							<< "\n\tfor MZ exec."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "win32")) {
						t	<< copyright()
							<<
						::std::endl
							<< "set platform to 'win32':"
							<< "\n\tnative MS-Windows XP (OS)"
							<< "\n\tfor PE exec."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "win64")) {
						t	<< copyright()
							<<
						::std::endl
							<< "set platform to 'win64':"
							<< "\n\tnative MS-Windows 10+ (OS)"
							<< "\n\tfor PE+ exec."
							<<
						::std::endl;
					}	else {
						t.str(::std::string());
						t	<< copyright()
							<<
						::std::endl
							<< "Unknown help option"
							<<
						::std::endl;
					}
				}	else {
					t	<< copyright()
						<<
					::std::endl
						<< "available platform options:"
						<< "\n\tdos16\tMS-DOS 6.20 16-Bit"
						<< "\n\tdos32\tFreeDOS 32-Bit"
						<< "\n\twin16\tMS-Windows 3.11"
						<< "\n\twin32\tMS-Windows XP, 10"
						<< "\n\tdos64\tMS-Windows 10+"
						<<
					::std::endl;
				}
			}
			
			// ----------------------
			// platform arch options:
			// ----------------------
			else if (s.at(0) == "arch") {
				t.str(::std::string());
				::kallup::setError(false);
				
				if (s.size() == 2)
				{
					::std::string s2 = s.at(1);
					if (s2.empty()) {
						::kallup::setError(true);
						t	<< copyright()
							<<
						::std::endl
							<< "No architecture option given !"
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "16")) {
						t	<< copyright()
							<<
						::std::endl
							<< "Architecture option:"
							<< "\n\tset arch to 16-Bit."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "32")) {
						t	<< copyright()
							<<
						::std::endl
							<< "Architecture option:"
							<< "\n\tset arch to 32-Bit."
							<<
						::std::endl;
					}	else
					if ((!s2.empty()) && (s2 == "64")) {
						t	<< copyright()
							<<
						::std::endl
							<< "Architecture option:"
							<< "\n\tset arch to 64-Bit."
							<<
						::std::endl;
					}	else {
						t.str(::std::string());
						t	<< copyright()
							<<
						::std::endl
							<< "Unknown help option"
							<<
						::std::endl;
					}
				}	else {
					t	<< copyright()
						<<
					::std::endl
						<< "available architecture options:"
						<< "\n\t16 - set arch to 16-Bit."
						<< "\n\t32 - set arch to 32-Bit."
						<< "\n\t64 - set arch to 64-Bit."
						<<
					::std::endl;
				}
			}			
			else {
				t.str(::std::string());
				t	<< copyright()
					<<
				::std::endl
					<< "Unknown help option"
					<<
				::std::endl;
			}
			#if defined(__MINGW32__) || defined(__MINGW64__)
			if (!isatty(fileno(stdout))) {
				::MessageBoxA(
					HWND(GetDesktopWindow()),
					LPCSTR(t.str().c_str()),
					LPCSTR("User-Information") ,
					UINT(MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL));
			}	else {
			#endif
			::std::cout << t.str() <<
			::std::endl ;
			#if defined(__MINGW32__) || defined(__MINGW64__)
			}
			#endif
			return SUCCESS;
		}

		// ----------------------------
		// output version:
		// ----------------------------
		if (vm.count("version")) {
			::std::stringstream t;
			t.str(::std::string());
			t	<< copyright()
				<<
			::std::endl
				<< "Version: " << __BUILD_VERSION__
				<<
			::std::endl;
			#if defined(__MINGW32__) || defined(__MINGW64__)
			if (!isatty(fileno(stdout))) {
				::MessageBoxA(
					HWND(GetDesktopWindow()),
					LPCSTR(t.str().c_str()),
					LPCSTR("User-Information") ,
					UINT(MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL));
			}	else {
			#endif
			#if defined(__MINGW32__) || defined(__MINGW64__)
				::std::cout << t.str();
			}
			#endif
		}

		// ----------------------------
		// operating system:
		// ----------------------------
		if (vm.count("platform")) {
			const ::std::string& s = vm["platform"].as<::std::string>();
			if (s == "dos16") ::kallup::appOption.platform = ::kallup::PlatformList::os_dos16; else
			if (s == "dos32") ::kallup::appOption.platform = ::kallup::PlatformList::os_dos32; else
			if (s == "win16") ::kallup::appOption.platform = ::kallup::PlatformList::os_win16; else
			if (s == "win32") ::kallup::appOption.platform = ::kallup::PlatformList::os_win32; else
			if (s == "win64") ::kallup::appOption.platform = ::kallup::PlatformList::os_win64;
			else {
				#if defined(__MINGW32__) || defined(__MINGW64__)
				::std::cout
					<< "Unknown Platform '"
					<< s
					<< "' in the --platform option." <<
				::std::endl;
				#endif
				return FAILURE;
			}

			::std::cout
				<< "platform is set to: "
				<< s <<
			::std::endl ;
		}

		// ----------------------------
		// set cpu architecture:
		// ----------------------------
		if (vm.count("arch")) {
			const uint8_t& s = vm["arch"].as<uint8_t>();
			if (s == 16) ::kallup::appOption.arch = ::kallup::ArchTypeList::arch_16Bit; else
			if (s == 32) ::kallup::appOption.arch = ::kallup::ArchTypeList::arch_32Bit; else
			if (s == 64) ::kallup::appOption.arch = ::kallup::ArchTypeList::arch_64Bit;
			else {
				#if defined(__MINGW32__) || defined(__MINGW64__)
				::std::cout
					<< "Unknown Arch '" << s <<
				::std::endl;
				#endif
				return FAILURE;
			}

			::std::cout
				<< "arch is set to: "
				<< vm["arch"].as<uint8_t>()
				<< " bit." <<
			::std::endl;
		}
		
		// ----------------------------
		// set output format
		// ----------------------------
		if (vm.count("format")) {
			const ::std::string& s = vm["format"].as<::std::string>();
			if (s == "coff") ::kallup::appOption.outFormat = ::kallup::OutputFormatList::format_coff; else
			if (s == "fpc" ) ::kallup::appOption.outFormat = ::kallup::OutputFormatList::format_fpc ; else
			if (s == "cpp" ) ::kallup::appOption.outFormat = ::kallup::OutputFormatList::format_cpp ; else
			if (s == "asm" ) ::kallup::appOption.outFormat = ::kallup::OutputFormatList::format_asm ;
			else {
				#if defined(__MINGW32__) || defined(__MINGW64__)
				::std::cout
					<< "output format = coff"
					<<
				::std::endl;
				#endif
			}
		}

		// ----------------------------------------------
		// check creditals, if login ok, next; else bye.
		// ----------------------------------------------

		// ----------------------------
		// entry start of application:
		// ----------------------------
		using namespace kallup;
		
		k32Bit* src = new k32Bit;
		k32Bit* dst = new k32Bit;
		kCOFF2* out = new kCOFF2;

		auto exec = new kBuildExec(src, dst, out);
	}
	catch (exception& e) {
		#if defined(__MINGW32__) || defined(__MINGW64__)
		::std::cerr << "error: " << e.what() <<
		::std::endl ;
		#endif
		return FAILURE;
	}
	catch (...) {
		#if defined(__MINGW32__) || defined(__MINGW64__)
		::std::cerr << "Exception of unknown type." <<
		::std::endl ;
		#endif
		return FAILURE;
	}
	
	return SUCCESS;
}
