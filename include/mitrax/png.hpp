//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__png__hpp_INCLUDED_
#define _mitrax__png__hpp_INCLUDED_

#include "matrix_interface.hpp"

#include <string>

#include <png++/png.hpp>


namespace mitrax{ namespace png{


	namespace detail{


		template < typename T >
		struct png_type;

		template <> struct png_type< char >
			{ using type = ::png::gray_pixel; };
		template <> struct png_type< signed char >
			{ using type = ::png::gray_pixel; };
		template <> struct png_type< unsigned char >
			{ using type = ::png::gray_pixel; };
		template <> struct png_type< std::int16_t >
			{ using type = ::png::gray_pixel_16; };
		template <> struct png_type< std::uint16_t >
			{ using type = ::png::gray_pixel_16; };

		template < typename T >
		using png_type_t = typename png_type< T >::type;


	}


	template < typename M, size_t Cols, size_t Rows >
	void load(matrix< M, Cols, Rows >& m, std::string const& filename){
		using value_type = value_type_t< M >;

		::png::image< detail::png_type_t< value_type > > output;
		output.read(filename);

		if(m.cols() != output.get_width() || m.rows() != output.get_height()){
			throw std::runtime_error("Can't load PNG-File, dims are wrong.");
		}

		for(std::size_t y = 0; y < output.get_height(); ++y){
			for(std::size_t x = 0; x < output.get_width(); ++x){
				m(x, y) = static_cast< value_type >(output[y][x]);
			}
		}
	}


	template < typename M, size_t Cols, size_t Rows >
	void save(matrix< M, Cols, Rows > const& m, std::string const& filename){
		using value_type = value_type_t< M >;
		using image_type = ::png::image< detail::png_type_t< value_type > >;
		using ivalue_type = typename image_type::traits::pixel_type;

		image_type output(m.cols(), m.rows());

		for(std::size_t y = 0; y < output.get_height(); ++y){
			for(std::size_t x = 0; x < output.get_width(); ++x){
				output[y][x] = static_cast< ivalue_type >(m(x, y));
			}
		}

		output.write(filename);
	}


} }


#endif