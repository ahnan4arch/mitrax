#include <benchmark/benchmark.h>

#include <Eigen/Core>

#include <mitrax/dim.hpp>

#include <algorithm>

#include "../../../include/random_vector.hpp"


using namespace mitrax;
using namespace mitrax::literals;


template < typename T >
[[gnu::noinline]]
void bm(benchmark::State& state, rt_dim_pair_t d){
	auto r = mitrax::random_vector< T >(d.point_count());

	while(state.KeepRunning()){
		Eigen::Matrix< T, Eigen::Dynamic, Eigen::Dynamic > m(
			size_t(d.cols()), size_t(d.rows())
		);

		std::copy(r.begin(), r.end(), m.data());

		benchmark::DoNotOptimize(m);
	}
}


#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>


namespace init{

	constexpr auto dimensions = boost::hana::make_tuple(
			dim_pair(2_CS, 2_RS),
			dim_pair(4_CS, 2_RS),
			dim_pair(8_CS, 2_RS),
			dim_pair(8_CS, 4_RS),
			dim_pair(8_CS, 8_RS),
			dim_pair(8_CS, 16_RS),
			dim_pair(8_CS, 32_RS),
			dim_pair(8_CS, 64_RS),
			dim_pair(16_CS, 64_RS),
			dim_pair(32_CS, 64_RS),
			dim_pair(64_CS, 64_RS),
			dim_pair(128_CS, 64_RS),
			dim_pair(256_CS, 64_RS),
			dim_pair(256_CS, 128_RS),
			dim_pair(256_CS, 256_RS)
		);

}

#include "main.hpp"
