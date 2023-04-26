#pragma once
#include <SDK.h>
using namespace alt;
class NativeContext : public INative::Context {
public:
	virtual ~NativeContext() {};
	virtual void Reset() override {}
	//
	virtual void Push(bool val) override {};
	virtual void Push(bool* val) override {};
	virtual void Push(int32_t val) override {}
	virtual void Push(int32_t* val) override {}
	virtual void Push(uint32_t val)  override {}
	virtual void Push(uint32_t* val) override {}
	virtual void Push(float val) override {}
	virtual void Push(float* val) override {};
	virtual void Push(alt::INative::Vector3* val)override {};
	virtual void Push(char* val)override {};
	virtual void Push(void* val)override {};
	
	virtual bool ResultBool()override {
		return false;
	};
	virtual int32_t ResultInt()override {
		return NULL;
	};
	virtual uint32_t ResultUint() override { return NULL; };
	virtual float ResultFloat() override { return NULL; };
	virtual alt::INative::Vector3 ResultVector3() override {
		return alt::INative::Vector3{};
	};
	const char* ResultString() override { return NULL; };
};

