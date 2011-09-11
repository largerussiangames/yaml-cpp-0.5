#ifndef VALUE_DETAIL_NODE_REF_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define VALUE_DETAIL_NODE_REF_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) || (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || (__GNUC__ >= 4)) // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif


#include "yaml-cpp/dll.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/node/ptr.h"
#include "yaml-cpp/node/detail/node_data.h"
#include <boost/utility.hpp>

namespace YAML
{
	namespace detail
	{
		class node_ref: private boost::noncopyable
		{
		public:
			node_ref() {}
			
			bool is_defined() const { return m_pData ? m_pData->is_defined() : false; }
			NodeType::value type() const { return m_pData ? m_pData->type() : NodeType::Undefined; }
			const std::string& scalar() const { return m_pData ? m_pData->scalar() : node_data::empty_scalar; }
			
			void mark_defined() { ensure_data_exists(); m_pData->mark_defined(); }
			void set_data(const node_ref& rhs) { m_pData = rhs.m_pData; }
			
			void set_type(NodeType::value type) { ensure_data_exists(); m_pData->set_type(type); }
			void set_null() { ensure_data_exists(); m_pData->set_null(); }
			void set_scalar(const std::string& scalar) { ensure_data_exists(); m_pData->set_scalar(scalar); }
			
			// size/iterator
			std::size_t size() const { return m_pData ? m_pData->size() : 0; }
			
			const_node_iterator begin() const { return m_pData ? static_cast<const node_data&>(*m_pData).begin() : const_node_iterator(); }
			node_iterator begin() {return m_pData ? m_pData->begin() : node_iterator(); }
			
			const_node_iterator end() const { return m_pData ? static_cast<const node_data&>(*m_pData).end() : const_node_iterator(); }
			node_iterator end() {return m_pData ? m_pData->end() : node_iterator(); }

			// sequence
			void append(node& node, shared_memory_holder pMemory) { ensure_data_exists(); m_pData->append(node, pMemory); }
			void insert(node& key, node& value, shared_memory_holder pMemory) {
				ensure_data_exists(); m_pData->insert(key, value, pMemory);
			}
			
			// indexing
			template<typename Key> node& get(const Key& key, shared_memory_holder pMemory) const { return m_pData ? static_cast<const node_data&>(*m_pData).get(key, pMemory) : pMemory->create_node(); }
			template<typename Key> node& get(const Key& key, shared_memory_holder pMemory) { ensure_data_exists(); return m_pData->get(key, pMemory); }
			template<typename Key> bool remove(const Key& key, shared_memory_holder pMemory) { return m_pData ? m_pData->remove(key, pMemory) : false; }
			
			node& get(node& key, shared_memory_holder pMemory) const { return m_pData ? static_cast<const node_data&>(*m_pData).get(key, pMemory) : pMemory->create_node(); }
			node& get(node& key, shared_memory_holder pMemory) { ensure_data_exists(); return m_pData->get(key, pMemory); }
			bool remove(node& key, shared_memory_holder pMemory) { return m_pData ? m_pData->remove(key, pMemory) : false; }
			
		private:
			void ensure_data_exists() { if(!m_pData) m_pData.reset(new node_data); }
			
		private:
			shared_node_data m_pData;
		};
	}
}

#endif // VALUE_DETAIL_NODE_REF_H_62B23520_7C8E_11DE_8A39_0800200C9A66
