

class abstract_test {

public:
	virtual void virt_next(int& i, int& sum) =0;

};

class test : public abstract_test {

public:
	virtual void virt_next(int& i, int& sum) override;
	void next(int& i, int& sum);
	inline void next_inline(int& i, int& sum) { sum+=i;i=-i;}
};

