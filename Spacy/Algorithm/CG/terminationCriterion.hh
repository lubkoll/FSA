// This file was automatically generated by friendly type erasure.
// Please do not modify.

#pragma once

#include <memory>
#include "Spacy/Util/table_util.hh"
#include "Detail/details_for_terminationCriterion.hh"

namespace Spacy
{

    namespace CG
    {
        /// Type-erased termination criterion for conjugate gradient methods.
        class TerminationCriterion
        {
        public:
            TerminationCriterion() noexcept;

            template < typename T,
                       typename std::enable_if< TerminationCriterionDetail::TerminationCriterionConcept<
                           TerminationCriterion, typename std::decay< T >::type >::value >::type* = nullptr >
            TerminationCriterion( T&& value )
                : functions_(
                      {&type_erasure_table_detail::delete_impl< typename std::decay< T >::type >,
                       &type_erasure_table_detail::clone_impl< typename std::decay< T >::type >,
                       &TerminationCriterionDetail::execution_wrapper< TerminationCriterion,
                                                                       typename std::decay< T >::type >::call,
                       &TerminationCriterionDetail::execution_wrapper< TerminationCriterion,
                                                                       typename std::decay< T >::type >::clear,
                       &TerminationCriterionDetail::execution_wrapper<
                           TerminationCriterion, typename std::decay< T >::type >::update_double_double_double_double,
                       &TerminationCriterionDetail::execution_wrapper< TerminationCriterion,
                                                                       typename std::decay< T >::type >::vanishingStep,
                       &TerminationCriterionDetail::execution_wrapper<
                           TerminationCriterion, typename std::decay< T >::type >::minimalDecreaseAchieved,
                       &TerminationCriterionDetail::execution_wrapper< TerminationCriterion,
                                                                       typename std::decay< T >::type >::setEps_double,
                       &TerminationCriterionDetail::execution_wrapper<
                           TerminationCriterion, typename std::decay< T >::type >::setAbsoluteAccuracy_double,
                       &TerminationCriterionDetail::execution_wrapper<
                           TerminationCriterion, typename std::decay< T >::type >::setMinimalAccuracy_double,
                       &TerminationCriterionDetail::execution_wrapper<
                           TerminationCriterion, typename std::decay< T >::type >::setRelativeAccuracy_double} ),
                  type_id_( typeid( typename std::decay< T >::type ).hash_code() ),
                  impl_( new typename std::decay< T >::type( std::forward< T >( value ) ) )
            {
            }

            TerminationCriterion( const TerminationCriterion& other );

            TerminationCriterion( TerminationCriterion&& other ) noexcept;

            ~TerminationCriterion();

            template < typename T,
                       typename std::enable_if< TerminationCriterionDetail::TerminationCriterionConcept<
                           TerminationCriterion, typename std::decay< T >::type >::value >::type* = nullptr >
            TerminationCriterion& operator=( T&& value )
            {
                return *this = TerminationCriterion( std::forward< T >( value ) );
            }

            TerminationCriterion& operator=( const TerminationCriterion& other );

            TerminationCriterion& operator=( TerminationCriterion&& other ) noexcept;

            /**
             * @brief Checks if the type-erased interface holds an implementation.
             * @return true if an implementation is stored, else false
             */
            explicit operator bool() const noexcept;

            bool operator()() const;

            void clear();

            void update( double alpha, double qAq, double qPq, double rPINVr );

            bool vanishingStep() const;

            bool minimalDecreaseAchieved() const;

            void setEps( double eps );

            void setAbsoluteAccuracy( double accuracy );

            void setMinimalAccuracy( double accuracy );

            void setRelativeAccuracy( double accuracy );

            /**
            * @brief Conversion of the stored implementation to @code  T* @endcode.
            * @return pointer to the stored object if conversion was successful, else nullptr
            */
            template < class T >
            T* target() noexcept
            {
                if ( !impl_ )
                    return nullptr;
                return type_erasure_table_detail::dynamic_cast_impl< T >( type_id_, impl_ );
            }

            /**
            * @brief Conversion of the stored implementation to @code const T* @endcode.
            * @return pointer to the stored object if conversion was successful, else nullptr
            */
            template < class T >
            const T* target() const noexcept
            {
                if ( !impl_ )
                    return nullptr;
                return type_erasure_table_detail::dynamic_cast_impl< T >( type_id_, impl_ );
            }

        private:
            void reset() noexcept;

            TerminationCriterionDetail::Functions< TerminationCriterion > functions_;
            std::size_t type_id_;
            void* impl_ = nullptr;
        };
    }
}