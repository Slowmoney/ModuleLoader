#pragma once
#include <SDK.h>

namespace core {
	//class IMValueImpl : public alt::IMValue
	//{
	//public:
	//	IMValueImpl(alt::IMValue::Type type): type(type) {}
	//	IMValueImpl(const IMValueImpl& rhs) {}
	//	IMValueImpl& operator=(const IMValueImpl& rhs) {}
	//	virtual alt::IMValue::Type GetType() const override {
	//		return type;
	//	};
	//	virtual std::string ToString() const override {
	//		return "";
	//	}
	//	virtual double ToNumber() const  override {
	//		return 0.0;
	//	}
	//	virtual MValue Clone() const override {
	//		alt::IMValue* mv = new IMValueImpl(*this);
	//		return MValue(mv);
	//	}
	//	virtual bool Equals(MValueConst other) const override {
	//		return false;
	//	};
	//	alt::IMValue::Type type;
	//};

	class IMValueNoneImpl: public alt::IMValueNone {
	public:
		IMValueNoneImpl() : type(alt::IMValue::Type::NONE) {}
		IMValueNoneImpl(const IMValueNoneImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueNone* mv = new IMValueNoneImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		alt::IMValue::Type type;
	};

	class IMValueNilImpl : public alt::IMValueNil {
	public:
		IMValueNilImpl() : type(alt::IMValue::Type::NIL) {}
		IMValueNilImpl(const IMValueNilImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueNil* mv = new IMValueNilImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		alt::IMValue::Type type;
	};

	class IMValueBoolImpl : public alt::IMValueBool {
	public:
		IMValueBoolImpl(bool val) : type(alt::IMValue::Type::BOOL), val(val) {}
		IMValueBoolImpl(const IMValueBoolImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueBool* mv = new IMValueBoolImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual bool Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		bool val;
	};

	class IMValueIntImpl : public alt::IMValueInt {
	public:
		IMValueIntImpl(int64_t val) : type(alt::IMValue::Type::INT), val(val) {}
		IMValueIntImpl(const IMValueIntImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueInt* mv = new IMValueIntImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual int64_t Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		int64_t val;
	};

	class IMValueUIntImpl : public alt::IMValueUInt {
	public:
		IMValueUIntImpl(int64_t val) : type(alt::IMValue::Type::UINT), val(val) {}
		IMValueUIntImpl(const IMValueUIntImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueUInt* mv = new IMValueUIntImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual uint64_t Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		uint64_t val;
	};

	class IMValueDoubleImpl : public alt::IMValueDouble {
	public:
		IMValueDoubleImpl(double val) : type(alt::IMValue::Type::DOUBLE), val(val) {}
		IMValueDoubleImpl(const IMValueDoubleImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueDouble* mv = new IMValueDoubleImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual double Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		double val;
	};

	class IMValueStringImpl : public alt::IMValueString {
	public:
		IMValueStringImpl(std::string val) : type(alt::IMValue::Type::STRING), val(val) {}
		IMValueStringImpl(const IMValueStringImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueString* mv = new IMValueStringImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual const std::string& Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		std::string val;
	};

	class IMValueListImpl : public virtual alt::IMValueList
	{
	public:
		IMValueListImpl(alt::Size size = 0) : type(alt::IMValue::Type::LIST) {
			this->data = std::vector<MValue>(size);
		}
		IMValueListImpl(const IMValueListImpl& rhs) {}
		virtual alt::Size GetSize() const override {
			return data.size();
		};
		virtual MValue Get(alt::Size i) override {
			return data[i];
		};
		virtual MValueConst Get(alt::Size i) const override {
			return data[i];
		};

		// Transfers ownership of MValue (You should not have any more refs to this copy)
		virtual void Set(alt::Size i, MValue val) override {
			data[i] = val;
		};
		virtual void Push(MValue val) override {
			data.push_back(val);
		};
		// Will clone an MValueConst
		virtual void SetConst(alt::Size i, MValueConst val) override {
			alt::IMValue* ss = (alt::IMValue*)val.Get();
			
			data[i] = MValue(ss);
		};
		virtual void PushConst(MValueConst val) override {
			alt::IMValue* ss = (alt::IMValue*)val.Get();
			data.push_back(MValue(ss));
		};
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueList* mv = new IMValueListImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		alt::IMValue::Type type;
		std::vector<MValue> data;
	};
	class IMValueDictImpl : public alt::IMValueDict {
	public:
		class Iterator : public alt::IMValueDict::Iterator
		{
			
		public:
			Iterator(std::unordered_map<std::string, MValue>::iterator begin, std::unordered_map<std::string, MValue>::iterator end): begin(begin), end(end) {}
			virtual std::string GetKey() override {
				return begin->first;
			};
			virtual MValueConst GetValue() override {
				return begin->second;
			};
			void Next() {
				begin++;
			}
			bool End() {
				return begin == end;
			}

			std::unordered_map<std::string, MValue>::iterator begin;
			std::unordered_map<std::string, MValue>::iterator end;
		};
		std::unordered_map<std::string, MValue>* data = new std::unordered_map<std::string, MValue>();
		IMValueDictImpl() : type(alt::IMValue::Type::DICT) {}
		IMValueDictImpl(const IMValueDictImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};

		virtual alt::Size GetSize() const override {
			return data->size();
		};

		virtual MValue Get(const std::string& key) override {
			auto it = data->find(key);
			if (it == data->end()) {
				alt::IMValueNone* s = new IMValueNoneImpl();
				return MValue(s);
			}
			return data->at(key);
		}
		
		virtual MValueConst Get(const std::string& key) const override {
			auto it = data->find(key);
			if (it == data->end()) {
				alt::IMValueNone* s = new IMValueNoneImpl();
				return MValueConst(s);
			}
			return data->at(key);
		};

		virtual void Set(const std::string& key, MValue val) override {
			data->insert({ key, val });
		}
		//
		virtual void SetConst(const std::string& key, MValueConst val) override {
			alt::IMValue* ss1 = (alt::IMValue*)val.Get();
			Set(key, MValue(ss1));
		}
		//
		virtual void Delete(const std::string& key)override {
			data->erase(key);
		};

		virtual Iterator* Begin() const override {
			std::unordered_map<std::string, MValue>::iterator begin = data->begin();
			std::unordered_map<std::string, MValue>::iterator end = data->end();
			Iterator* it = new Iterator(begin, end);
			iterator = it;
			return it;
		};
		virtual Iterator* Next() const override {
			iterator->Next();
			if (iterator->End()) return NULL;
			return iterator;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValue* mv = new IMValueDictImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			if (other->GetType() == core::IMValue::Type::DICT) {
				auto dict = other.As<alt::IMValueDict>();
				for (auto it = dict->Begin(); it; it = dict->Next()) {
					auto has = data->find(it->GetKey());
					if (has == data->end()) return false;
					if (!it->GetValue()->Equals(has->second)) return false;
				}
				return true;
			}
			return other->GetType() == type;
		};
		static  core::IMValueDictImpl::Iterator* iterator;
		alt::IMValue::Type type;
	};


	class IMValueVector2Impl : public alt::IMValueVector2 {
	public:
		IMValueVector2Impl(alt::Vector2f val) : type(alt::IMValue::Type::VECTOR2), val(val) {}
		IMValueVector2Impl(const IMValueVector2Impl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueVector2* mv = new IMValueVector2Impl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual alt::Vector2f Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		alt::Vector2f val;
	};

	class IMValueVector3Impl : public alt::IMValueVector3 {
	public:
		IMValueVector3Impl(alt::Vector3f val) : type(alt::IMValue::Type::VECTOR3), val(val) {}
		IMValueVector3Impl(const IMValueVector3Impl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueVector3* mv = new IMValueVector3Impl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual alt::Vector3f Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		alt::Vector3f val;
	};

	class IMValueRGBAImpl : public alt::IMValueRGBA {
	public:
		IMValueRGBAImpl(alt::RGBA val) : type(alt::IMValue::Type::RGBA), val(val) {}
		IMValueRGBAImpl(const IMValueRGBAImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueRGBA* mv = new IMValueRGBAImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual alt::RGBA Value() const override {
			return val;
		};
		alt::IMValue::Type type;
		alt::RGBA val;
	};

	class IMValueFunctionImpl : public alt::IMValueFunction {
	public:
		IMValueFunctionImpl(const alt::IMValueFunction::Impl* impl) : type(alt::IMValue::Type::FUNCTION), impl(impl) {}
		IMValueFunctionImpl(const IMValueFunctionImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueFunction* mv = new IMValueFunctionImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};
		virtual MValue Call(alt::MValueArgs args) const override {
			return impl->Call(args);
		};
		alt::IMValue::Type type;
		const alt::IMValueFunction::Impl* impl;
	};
	class IMValueBaseObjectImpl : public alt::IMValueBaseObject {
	public:
		IMValueBaseObjectImpl(alt::IBaseObject* value) : type(alt::IMValue::Type::BASE_OBJECT), value(value) {}
		IMValueBaseObjectImpl(const IMValueBaseObjectImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueBaseObject* mv = new IMValueBaseObjectImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};

		virtual alt::IBaseObject* RawValue() const override {
			return value;
		};;
		virtual std::shared_ptr<alt::IBaseObject> Value() const override {
			core::BaseObject* tt = (core::BaseObject*)value;
			core::BaseObject ss = *tt;
			auto ob = std::make_shared<core::BaseObject>(ss);

			return (std::shared_ptr<alt::IBaseObject>)ob;
		};

		alt::IBaseObject* value;
		alt::IMValue::Type type;
		
	};

	class IMValueByteArrayImpl : public alt::IMValueByteArray {
	public:
		IMValueByteArrayImpl(Size size) : type(alt::IMValue::Type::BYTE_ARRAY), size(size) {
			this->data = (uint8_t*)std::malloc(size);
		}
		IMValueByteArrayImpl(const uint8_t* data, Size size) : type(alt::IMValue::Type::BYTE_ARRAY), size(size) {
			this->data = (uint8_t*)std::malloc(size);
			std::memcpy(this->data, data, size);
		}
		IMValueByteArrayImpl(const IMValueByteArrayImpl& rhs) {}
		virtual alt::IMValue::Type GetType() const override {
			return type;
		};
		virtual std::string ToString() const override {
			return "";
		}
		virtual double ToNumber() const  override {
			return 0.0;
		}
		virtual MValue Clone() const override {
			alt::IMValueByteArray* mv = new IMValueByteArrayImpl(*this);
			return MValue(mv);
		}
		virtual bool Equals(MValueConst other) const override {
			return other->GetType() == type;
		};

		virtual Size GetSize() const override {
			return size;
		};;
		virtual const uint8_t* GetData() const override {
			return data;
		};;
		virtual uint8_t* GetData() override {
			return data;
		};;

		alt::IMValue::Type type;
		Size size;
		uint8_t* data;
	};
}

core::IMValueDictImpl::Iterator* core::IMValueDictImpl::iterator = (core::IMValueDictImpl::Iterator *)0;
