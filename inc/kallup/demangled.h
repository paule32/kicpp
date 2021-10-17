// ------------------------------------------------------------------
// file:   kitest.h
// desc:   example file for creating a simple AI program for kidding.
//
// autor:  Jens Kallup - <kallup.jens@web.de>
//         kallup.net * non-profit
// date:   2021-10-12
//
// policy: only for education usage !!! - no commercial use allowed.
//         free to distribute if copyright notice is intact.
// ------------------------------------------------------------------
#pragma once
#ifndef  DEMANGLED_H_
# define DEMANGLED_H_

# define USE_BOOST 0

# include "kallup/common.h"

// ----------------------------------------
// just a namespace, to avoid cross overs:
// ----------------------------------------
namespace kallup
{
	enum FieldStates : uint8_t {
		FS_NOK     =  0,	// not okay; unknown
		FS_OK      =  1,	// ok, commmon
		FS_INIT    =  2,	// ok, but not create *or* destroyed
		FS_CREATED =  4,	// ok, object created ?
		FS_DESTROY =  8,
		FS_PENDING = 16
	};
	FieldStates fieldState = FieldStates::FS_NOK;

	// -----------------------------------------------
	// all what we known is, that we known nothing :-)
	// the mother of all. here as dummy ...
	// -----------------------------------------------
	class isUnknown {
	public:
		virtual ~isUnknown() = 0;
	};
	isUnknown::~isUnknown() {
		::std::cout << "all is over :(" <<
		::std::endl ;
	}

	// ----------------------------------------------------------
	// we assume that we have two god's (lazarus, and christy).
	// we assume that all of these characters have two mind laps.
	// so, we have 4 choiches (2 x 2 = 4), and 3 states for both:
	// 1: before, 2: now, 3: after.
	// we can extend out universe with derivated template classes
	// and class members.
	// when we extend to a property, keep in mind, tha sender.
	// ----------------------------------------------------------
	class Base: public isUnknown {
	private:
		class Base * prev;
		class Base * next;

		::std::chrono::time_point < ::std::chrono::system_clock > time_create;        // object created on
		::std::chrono::time_point < ::std::chrono::system_clock > time_destroy;       // destroyed on

		::std::chrono::time_point < ::std::chrono::system_clock > time_pending;       // time queued since
		::std::chrono::time_point < ::std::chrono::system_clock > time_expect;        // time until finish task
	public:
		::std::chrono::time_point < ::std::chrono::system_clock > getTime_Pending() const;
		::std::chrono::time_point < ::std::chrono::system_clock > getTime_Create () const;
		::std::chrono::time_point < ::std::chrono::system_clock > getTime_Expect () const;
		::std::chrono::time_point < ::std::chrono::system_clock > getTime_Destroy() const;

		void setTime_Pending ( ::std::chrono::time_point < ::std::chrono::system_clock >);
		void setTime_Create  ( ::std::chrono::time_point < ::std::chrono::system_clock >);
		void setTime_Expect  ( ::std::chrono::time_point < ::std::chrono::system_clock >);
		void setTime_Destroy ( ::std::chrono::time_point < ::std::chrono::system_clock >);
	public:
		friend ::std::istream& operator >> (::std::istream&, class Base&);
		friend ::std::ostream& operator << (::std::ostream&, ::std::chrono::time_point < ::std::chrono::system_clock >&);
		
		Base(const ::std::chrono::time_point < ::std::chrono::system_clock >&);
		Base();

		~Base();
	};

	// ctor: constructor's
	Base::Base(const ::std::chrono::time_point < ::std::chrono::system_clock >& v) {
		time_create = v;
	}
	Base::Base() {
		auto start  = ::std::chrono::system_clock::now();
		time_create = start;
	}

	// dtor: destructor - free memory
	Base::~Base()
	{
		::std::cout << "delete *Base ..." <<
		::std::endl ;

		delete next;
		delete prev;
	}

	// time getter:
	::std::chrono::time_point < ::std::chrono::system_clock > Base::getTime_Pending () const { return time_pending; }
	::std::chrono::time_point < ::std::chrono::system_clock > Base::getTime_Create  () const { return time_create ; }
	::std::chrono::time_point < ::std::chrono::system_clock > Base::getTime_Expect  () const { return time_expect ; }
	::std::chrono::time_point < ::std::chrono::system_clock > Base::getTime_Destroy () const { return time_destroy; }

	// time setter:
	void Base::setTime_Pending ( ::std::chrono::time_point < ::std::chrono::system_clock > val ) { time_pending = val; }
	void Base::setTime_Create  ( ::std::chrono::time_point < ::std::chrono::system_clock > val ) { time_create  = val; }
	void Base::setTime_Expect  ( ::std::chrono::time_point < ::std::chrono::system_clock > val ) { time_expect  = val; }
	void Base::setTime_Destroy ( ::std::chrono::time_point < ::std::chrono::system_clock > val ) { time_destroy = val; }

	// object output streamer:
	::std::ofstream& operator << (::std::ofstream& os, const class Base* obj) {
		::std::cout << "save crete time:" << std::endl;
		::std::time_t tc =
		::std::chrono::system_clock::to_time_t(obj->getTime_Create());
		::std::tm local = *
		::std::localtime(&tc);

		os.write(reinterpret_cast<char*>(&local.tm_year), sizeof(local.tm_year));
		os.write(reinterpret_cast<char*>(&local.tm_mon ), sizeof(local.tm_mon ));
		os.write(reinterpret_cast<char*>(&local.tm_hour), sizeof(local.tm_hour));
		os.write(reinterpret_cast<char*>(&local.tm_min ), sizeof(local.tm_min ));
		os.write(reinterpret_cast<char*>(&local.tm_sec ), sizeof(local.tm_sec ));

		::std::cout << "save pending time:" << std::endl;   tc =
		::std::chrono::system_clock::to_time_t(obj->getTime_Pending()); local = *
		::std::localtime(&tc);

		os.write(reinterpret_cast<char*>(&local.tm_year), sizeof(local.tm_year));
		os.write(reinterpret_cast<char*>(&local.tm_mon ), sizeof(local.tm_mon ));
		os.write(reinterpret_cast<char*>(&local.tm_hour), sizeof(local.tm_hour));
		os.write(reinterpret_cast<char*>(&local.tm_min ), sizeof(local.tm_min ));
		os.write(reinterpret_cast<char*>(&local.tm_sec ), sizeof(local.tm_sec ));

		::std::cout << "save expect time:" << std::endl;    tc =
		::std::chrono::system_clock::to_time_t(obj->getTime_Expect());  local = *
		::std::localtime(&tc);

		os.write(reinterpret_cast<char*>(&local.tm_year), sizeof(local.tm_year));
		os.write(reinterpret_cast<char*>(&local.tm_mon ), sizeof(local.tm_mon ));
		os.write(reinterpret_cast<char*>(&local.tm_hour), sizeof(local.tm_hour));
		os.write(reinterpret_cast<char*>(&local.tm_min ), sizeof(local.tm_min ));
		os.write(reinterpret_cast<char*>(&local.tm_sec ), sizeof(local.tm_sec ));

		::std::cout << "save destroy time:" << std::endl;   tc =
		::std::chrono::system_clock::to_time_t(obj->getTime_Destroy()); local = *
		::std::localtime(&tc);

		os.write(reinterpret_cast<char*>(&local.tm_year), sizeof(local.tm_year));
		os.write(reinterpret_cast<char*>(&local.tm_mon ), sizeof(local.tm_mon ));
		os.write(reinterpret_cast<char*>(&local.tm_hour), sizeof(local.tm_hour));
		os.write(reinterpret_cast<char*>(&local.tm_min ), sizeof(local.tm_min ));
		os.write(reinterpret_cast<char*>(&local.tm_sec ), sizeof(local.tm_sec ));
		
		return os;
	}
	::std::ostream& operator << (::std::ostream& os, class Base& obj) {
		::std::cout << "llllooo" << ::std::endl;
		return os;
	}

	::std::ostream& operator << (::std::ostream& os, ::std::chrono::time_point < ::std::chrono::system_clock >& val)  {
		::std::cout << "mmmmmm\n";
		//char* letter = reinterpret_cast<char*>(val.tv_sec);
		//os << letter;
		return os;
	}
	
	// object input streamer:
	::std::istream& operator >> (::std::istream& is, class Base& obj) {
		::std::cout << "read crete time:" << std::endl;
		return is;
	}

	// -----------------------------------------------
	// helper wrappers:
	// -----------------------------------------------
	template <class T>
	inline bool operator != (const T& lhs, const T& rhs) {
		if (lhs != rhs)
		return true;
		return false;
	}

	template <class T>
	inline bool operator == (const T& lhs, const T& rhs) {
		if (lhs == rhs)
		return true;
		return false;
	}

	template <class T>
	inline bool operator < (const T& lhs, const T& rhs) {
		if (lhs == rhs)
		return true;
		return false;
	}

	// -----------------------------------------------
	// our data base states :-)
	// -----------------------------------------------
	struct isState {
		class Base * before = nullptr;
		class Base * after  = nullptr;
	};

	template <isState& before, isState& after>
	class isGOD: public Base {
	public:
	};
	
	template <isState& before, isState& after>
	class isLAZ: public Base {
	public:
	};

	void init()
	{
		// ---------------------------
		// you can think your own :-)
		// ---------------------------
		static isState nothing;

		Base *god_before = new isGOD<nothing, nothing>;
		Base *laz_before = new isLAZ<nothing, nothing>;

		::std::ofstream save("memory.dat",
		::std::ios::out |
		::std::ios::binary);

		save << "before|";
		save << god_before;
		save << "|after";
		
		save.close();

		delete laz_before;
		delete god_before;
	};
	
};      // namespace: kallup

int main()
{
	kallup::init();
	return SUCCESS;
}

#endif  // #ifdef:    DEMANGLED_H_
