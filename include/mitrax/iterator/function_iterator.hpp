//-----------------------------------------------------------------------------
// Copyright (c) 2016 Benjamin Buch
//
// https://github.com/bebuch/mitrax
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _mitrax__iterator__function_iterator__hpp_INCLUDED_
#define _mitrax__iterator__function_iterator__hpp_INCLUDED_

#include "../dim.hpp"

#include <iterator>


namespace mitrax{


	template < typename F >
	class function_iterator{
	public:
		using function_type = F;

		using difference_type = std::ptrdiff_t;

		using pointer = void;

		using value_type = decltype(std::declval< F >()(size_t()));

		using iterator_category = std::random_access_iterator_tag;

		using reference = value_type;


		constexpr explicit function_iterator(F&& f, size_t i = 0):
			f_(static_cast< F&& >(f)), n_(i) {}

		constexpr function_iterator(function_iterator&& u) = default;

		constexpr function_iterator(function_iterator const& u) = default;


		constexpr function_iterator& operator=(function_iterator&& u)
			= default;

		constexpr function_iterator& operator=(function_iterator const& u)
			= default;


		constexpr size_t pos()const{
			return n_;
		}

		constexpr decltype(auto) operator*()const{
			return f_(n_);
		}

		constexpr decltype(auto) operator[](difference_type n)const{
			return f_(n_ + n);
		}



		constexpr function_iterator& operator++(){
			++n_;
			return *this;
		}

		constexpr function_iterator operator++(int){
			return function_iterator(n_++);
		}

		constexpr function_iterator& operator--(){
			--n_;
			return *this;
		}

		constexpr function_iterator operator--(int){
			return function_iterator(n_--);
		}


		constexpr function_iterator operator+(difference_type n)const{
			return function_iterator(n_ + n);
		}

		constexpr function_iterator& operator+=(difference_type n){
			n_ += n;
			return *this;
		}

		constexpr function_iterator operator-(difference_type n)const{
			return function_iterator(n_ - n);
		}

		constexpr function_iterator& operator-=(difference_type n){
			n_ -= n;
			return *this;
		}


	private:
		F f_;
		size_t n_;
	};


	template < typename F1, typename F2 >
	constexpr bool operator==(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() == rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator!=(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() != rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator<(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() < rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator<=(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() <= rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator>(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() > rhs.pos();
	}

	template < typename F1, typename F2 >
	constexpr bool operator>=(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() >= rhs.pos();
	}

	template < typename F >
	constexpr function_iterator< F > operator+(
		typename function_iterator< F >::difference_type n,
		function_iterator< F > const& iter
	){
		return function_iterator< F >(iter + n);
	}

	template < typename F1, typename F2 >
	constexpr auto operator-(
		function_iterator< F1 > const& lhs, function_iterator< F2 > const& rhs
	){
		return lhs.pos() - rhs.pos();
	}


	template < typename F >
	constexpr function_iterator< F >
	make_function_iterator(F&& f, size_t n = 0){
		return function_iterator< F >(static_cast< F&& >(f), n);
	}


	template < typename F, bool Cct, size_t C >
	class function_xy_adapter{
	public:
		constexpr function_xy_adapter(F&& f, col_t< Cct, C > cols)
			noexcept(noexcept(F(static_cast< F&& >(f)))):
			f_(static_cast< F&& >(f)), cols_(cols) {}

		constexpr decltype(auto) operator()(size_t i)
		noexcept(noexcept(std::declval< F >()(size_t(), size_t()))){
			return f_(i % size_t(cols_), i / size_t(cols_));
		}

	private:
		F f_;
		col_t< Cct, C > cols_;
	};

	template < typename F, bool Cct, size_t C >
	constexpr auto make_function_xy_adapter(F&& f, col_t< Cct, C > cols){
		return function_xy_adapter< F, Cct, C >(static_cast< F&& >(f), cols);
	}


}


#endif