#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class BaseSynthComponent
{
public:
    BaseSynthComponent() {}
    void setValue(string name, double value) { values_[name] = value; }
    vector<string> keys() {
        vector<string> retval;
        for (const auto pair: values_) {
            retval.push_back(pair.first);
        }
        return retval;
    }
    virtual double getOutput() { return 1.0; }
protected:
    map<string, double> values_;
};

class FakeFM : public BaseSynthComponent
{
public:
    FakeFM() {
        values_["ratio"] = 1.0;
        setValue("index", 1.0);
        setValue("feedbackIndex", 1.0);
        setValue("frequencyHz_", 440.0);
        modulator_ = new BaseSynthComponent();
        carrier_ = new BaseSynthComponent();
    }
    double getOutput() {
        /*
        double modulation = modulator_->getOutput();
        double modulationAmount = (values_["index_"] * modulation);
        double feedbackAmount = values_["feedbackIndex_"] * previousSample_;
        carrier_->setValue("frequencyHz_",
            values_["frequencyHz_"] + modulationAmount + feedbackAmount
        );
        double carrierOut = carrier_->getOutput();
        previousSample_ = carrierOut;
        return 2.0;
        */
        return values_["XXX"];
    }
    double previousSample_ = 0.0;
    BaseSynthComponent *carrier_, *modulator_;
};

int main () {
    vector<BaseSynthComponent*> list;
    FakeFM *fm = new FakeFM();
    for (auto key: fm->keys()) {
        cout << key << "\n";
    }
    BaseSynthComponent *base = new BaseSynthComponent();
    list.push_back(fm);
    list.push_back(base);
    list[0]->setValue("XXX", 777);
    for (auto component: list) {
        cout << component->getOutput() << "\n";
    }
}
