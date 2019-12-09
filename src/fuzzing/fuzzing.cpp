
#include "../Implem/map_tree/map_tree.hpp"
#include "fuzzing_helper.hpp"
#include "fuzz_targets.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) 
{
	using namespace NIndexedContainer;
	using Container =
		n_indexed<
			int, map_tree_storage, 
			indexes<int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int>, 
			traits<filter_trait, random_access_trait, size_trait, remove_trait>>;

	FuzzingHelper::fuzz_stream stream{ data, size };
	Container c;
	
	FuzzingHelper::function_fuzzer(1024, random_access_fuzz{ c }, stream);
	FuzzingHelper::function_fuzzer(1024, filter_fuzz{ c }, stream);
	FuzzingHelper::function_fuzzer(1024, remove_fuzz{ c }, stream);

	return 0;  
}

