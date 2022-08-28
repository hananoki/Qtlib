#pragma once

#include <QList>
#include "cpplinq.hpp"

namespace cpplinq {
	namespace detail {
		struct to_qlist_builder : base_builder {
			typedef                 to_qlist_builder       this_type;

			CPPLINQ_INLINEMETHOD explicit to_qlist_builder() CPPLINQ_NOEXCEPT {
			}

			CPPLINQ_INLINEMETHOD to_qlist_builder( to_list_builder const& v ) CPPLINQ_NOEXCEPT {
			}

			CPPLINQ_INLINEMETHOD to_qlist_builder( to_list_builder&& v ) CPPLINQ_NOEXCEPT {
			}

			template<typename TRange>
			CPPLINQ_METHOD QList<typename TRange::value_type> build( TRange range ) const {
				QList<typename TRange::value_type> result;

				while( range.next() ) {
					result.push_back( range.front() );
				}

				return result;
			}

		};
	}

	CPPLINQ_INLINEMETHOD detail::to_qlist_builder to_qlist() CPPLINQ_NOEXCEPT {
		return detail::to_qlist_builder();
	}
}
