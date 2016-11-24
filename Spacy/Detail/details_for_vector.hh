// This file was automatically generated by friendly type erasure.
// Please do not modify.

// @cond TYPE_ERASURE_DETAIL
#pragma once

#include <memory>
#include <type_traits>
#include <functional>
#include <Spacy/Spaces/ScalarSpace/real.hh>
#include <Spacy/Util/Exceptions/incompatibleSpaceException.hh>
#include <Spacy/Util/Mixins/get.hh>
#include <Spacy/Util/table_util.hh>
#include <Spacy/vectorSpace.hh>

namespace Spacy
{
    namespace VectorDetail
    {
        template < class Interface, class Buffer >
        struct Functions
        {
            using clone_function = void ( * )( void*, std::shared_ptr< void >& );
            using clone_into_function = void ( * )( void*, Buffer&, std::shared_ptr< void >& );
            using call_const_Vector_ref_function = Real ( * )( const Interface&, void*, void* x );
            using add_const_Vector_ref_function = Interface& (*)( Interface&, void*, void* y );
            using subtract_const_Vector_ref_function = Interface& (*)( Interface&, void*, void* y );
            using multiply_double_function = Interface& (*)( Interface&, void*, double a );
            using negate_function = Interface ( * )( const Interface&, void* );
            using compare_const_Vector_ref_function = bool ( * )( const Interface&, void*, void* y );
            using space_function = const VectorSpace& (*)( const Interface&, void* );

            clone_function clone;
            clone_into_function clone_into;
            call_const_Vector_ref_function call_const_Vector_ref;
            add_const_Vector_ref_function add_const_Vector_ref;
            subtract_const_Vector_ref_function subtract_const_Vector_ref;
            multiply_double_function multiply_double;
            negate_function negate;
            compare_const_Vector_ref_function compare_const_Vector_ref;
            space_function space;
        };

        template < class Interface, class Impl >
        struct execution_wrapper
        {
            static Real call_const_Vector_ref( const Interface& interface, void* impl, void* x )
            {
                return static_cast< const Impl* >( impl )->operator()( *static_cast< const Impl* >( x ) );
            }

            static Interface& add_const_Vector_ref( Interface& interface, void* impl, void* y )
            {
                static_cast< Impl* >( impl )->operator+=( *static_cast< Impl* >( y ) );
                return interface;
            }

            static Interface& subtract_const_Vector_ref( Interface& interface, void* impl, void* y )
            {
                static_cast< Impl* >( impl )->operator-=( *static_cast< Impl* >( y ) );
                return interface;
            }

            static Interface& multiply_double( Interface& interface, void* impl, double a )
            {
                static_cast< Impl* >( impl )->operator*=( std::move( a ) );
                return interface;
            }

            static Interface negate( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->operator-();
            }

            static bool compare_const_Vector_ref( const Interface& interface, void* impl, void* y )
            {
                return static_cast< const Impl* >( impl )->operator==( *static_cast< const Impl* >( y ) );
            }

            static const VectorSpace& space( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->space();
            }
        };

        template < class Interface, class Impl >
        struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
        {
            static Real call_const_Vector_ref( const Interface& interface, void* impl, void* x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()(
                    static_cast< std::reference_wrapper< Impl >* >( x )->get() );
            }

            static Interface& add_const_Vector_ref( Interface& interface, void* impl, void* y )
            {
                static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator+=(
                    static_cast< std::reference_wrapper< Impl >* >( y )->get() );
                return interface;
            }

            static Interface& subtract_const_Vector_ref( Interface& interface, void* impl, void* y )
            {
                static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator-=(
                    static_cast< std::reference_wrapper< Impl >* >( y )->get() );
                return interface;
            }

            static Interface& multiply_double( Interface& interface, void* impl, double a )
            {
                static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator*=( std::move( a ) );
                return interface;
            }

            static Interface negate( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator-();
            }

            static bool compare_const_Vector_ref( const Interface& interface, void* impl, void* y )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator==(
                    static_cast< std::reference_wrapper< Impl >* >( y )->get() );
            }

            static const VectorSpace& space( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().space();
            }
        };

        template < class T >
        using TryMemFn_call_const_Vector_ref = decltype( std::declval< T >().operator()( std::declval< T >() ) );
        template < class T, class = void >
        struct HasMemFn_call_const_Vector_ref : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_call_const_Vector_ref<
            T, type_erasure_table_detail::voider< TryMemFn_call_const_Vector_ref< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_add_const_Vector_ref = decltype( std::declval< T >().operator+=( std::declval< T >() ) );
        template < class T, class = void >
        struct HasMemFn_add_const_Vector_ref : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_add_const_Vector_ref< T,
                                              type_erasure_table_detail::voider< TryMemFn_add_const_Vector_ref< T > > >
            : std::true_type
        {
        };
        template < class T >
        using TryMemFn_subtract_const_Vector_ref = decltype( std::declval< T >().operator-=( std::declval< T >() ) );
        template < class T, class = void >
        struct HasMemFn_subtract_const_Vector_ref : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_subtract_const_Vector_ref<
            T, type_erasure_table_detail::voider< TryMemFn_subtract_const_Vector_ref< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_multiply_double = decltype( std::declval< T >().operator*=( std::declval< double >() ) );
        template < class T, class = void >
        struct HasMemFn_multiply_double : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_multiply_double< T, type_erasure_table_detail::voider< TryMemFn_multiply_double< T > > >
            : std::true_type
        {
        };
        template < class T >
        using TryMemFn_negate = decltype( std::declval< T >().operator-() );
        template < class T, class = void >
        struct HasMemFn_negate : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_negate< T, type_erasure_table_detail::voider< TryMemFn_negate< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_compare_const_Vector_ref = decltype( std::declval< T >().operator==( std::declval< T >() ) );
        template < class T, class = void >
        struct HasMemFn_compare_const_Vector_ref : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_compare_const_Vector_ref<
            T, type_erasure_table_detail::voider< TryMemFn_compare_const_Vector_ref< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_space = decltype( std::declval< T >().space() );
        template < class T, class = void >
        struct HasMemFn_space : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_space< T, type_erasure_table_detail::voider< TryMemFn_space< T > > > : std::true_type
        {
        };

        template < class T >
        using VectorConceptImpl = std::integral_constant<
            bool,
            HasMemFn_call_const_Vector_ref< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                HasMemFn_add_const_Vector_ref< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                HasMemFn_subtract_const_Vector_ref<
                    type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                HasMemFn_multiply_double< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                HasMemFn_negate< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                HasMemFn_compare_const_Vector_ref<
                    type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                HasMemFn_space< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value >;

        template < class Impl, class T, bool = std::is_same< Impl, T >::value >
        struct VectorConcept : std::false_type
        {
        };
        template < class Impl, class T >
        struct VectorConcept< Impl, T, false > : VectorConceptImpl< T >
        {
        };
    }
}

//@endcond
