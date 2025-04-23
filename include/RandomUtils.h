#ifndef _randomutils_h
#define _randomutils_h

class RandomUtils {
	public:
		RandomUtils();

		template<typename ForwardIt>
		void shuffler(ForwardIt first, ForwardIt last);
	
	private:
		unsigned ru_seed{};
};

#endif