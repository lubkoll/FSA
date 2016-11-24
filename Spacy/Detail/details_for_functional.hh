// This file was automatically generated by friendly type erasure.
// Please do not modify.

// @cond TYPE_ERASURE_DETAIL
#pragma once

#include <memory>
#include <functional>
#include <Spacy/Spaces/ScalarSpace/real.hh>
#include <Spacy/Util/table_util.hh>
#include <Spacy/vector.hh>
#include <Spacy/vectorSpace.hh>

namespace Spacy
{
    namespace FunctionalDetail
    {
        template < class Interface, class Buffer >
        struct Functions
        {
            using clone_function = void ( * )( void*, std::shared_ptr< void >& );
            using clone_into_function = void ( * )( void*, Buffer&, std::shared_ptr< void >& );
            using call_const_Vector_ref_function = Real ( * )( const Interface&, void*, const Vector& x );
            using domain_function = const VectorSpace& (*)( const Interface&, void* );

            clone_function clone;
            clone_into_function clone_into;
            call_const_Vector_ref_function call_const_Vector_ref;
            domain_function domain;
        };

        template < class Interface, class Impl >
        struct execution_wrapper
        {
            static Real call_const_Vector_ref( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< const Impl* >( impl )->operator()( x );
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->domain();
            }
        };

        template < class Interface, class Impl >
        struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
        {
            static Real call_const_Vector_ref( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()( x );
            }

            static const VectorSpace& domain( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().domain();
            }
        };

        template < class T >
        using TryMemFn_call_const_Vector_ref = decltype( std::declval< T >().operator()( std::declval< Vector >() ) );
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
        using TryMemFn_domain = decltype( std::declval< T >().domain() );
        template < class T, class = void >
        struct HasMemFn_domain : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_domain< T, type_erasure_table_detail::voider< TryMemFn_domain< T > > > : std::true_type
        {
        };

        template < class T >
        using FunctionalConceptImpl = std::integral_constant<
            bool, HasMemFn_call_const_Vector_ref< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                      HasMemFn_domain< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value >;

        template < class Impl, class T, bool = std::is_same< Impl, T >::value >
        struct FunctionalConcept : std::false_type
        {
        };
        template < class Impl, class T >
        struct FunctionalConcept< Impl, T, false > : FunctionalConceptImpl< T >
        {
        };
    }
}

//@endcond
