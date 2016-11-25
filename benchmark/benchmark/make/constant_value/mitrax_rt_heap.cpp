#include <benchmark/benchmark.h>

#include <mitrax/operator.hpp>


using namespace mitrax;
using namespace mitrax::literals;


template < typename T, typename D >
void BM_make(benchmark::State& state, T v, D d1){
	while(state.KeepRunning()){
		auto m = make_matrix_v(d1, v);

		benchmark::DoNotOptimize(m);
	}
}

int main(int argc, char** argv){
	using f4 = float;

	for(auto& d1: std::vector< auto_dim_pair_t< 0, 0 > >{
		{2_Cd, 2_Rd},
		{4_Cd, 2_Rd},
		{8_Cd, 2_Rd},
		{8_Cd, 4_Rd},
		{8_Cd, 8_Rd},
		{8_Cd, 16_Rd},
		{8_Cd, 32_Rd},
		{8_Cd, 64_Rd},
		{16_Cd, 64_Rd},
		{32_Cd, 64_Rd},
		{64_Cd, 64_Rd},
		{128_Cd, 64_Rd},
		{256_Cd, 64_Rd},
		{256_Cd, 128_Rd},
		{256_Cd, 256_Rd}
	}){
		benchmark::RegisterBenchmark(
			std::to_string(d1.point_count()).c_str(),
			BM_make< f4, auto_dim_pair_t< 0, 0 > >, 5, d1
		);
	}

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();
}
