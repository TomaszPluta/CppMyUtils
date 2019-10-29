#include <memory>


#include <algorithm>
#include <vector>

#include <iostream>
#include <string_view>

class Observer{
public:
	virtual ~Observer() = default;
	virtual int getId() = 0;
	virtual void update() = 0;
};

using ObserverPtr = std::shared_ptr<Observer>;





class isEqualTo final{
public:
	explicit isEqualTo(const ObserverPtr &observer) : observer{observer}{};
bool operator()(const ObserverPtr &observerToCompare){
	return observer->getId() == observerToCompare->getId();
}


private:
	ObserverPtr observer;

};




class Subject{
public:
	void addObserver(ObserverPtr & observerToAdd){
		if (std::find_if(observers.begin(), observers.end(), isEqualTo(observerToAdd)) == observers.end()){
			observers.push_back(observerToAdd);
		}
	}

	void removeObserver(ObserverPtr & observerToRemove){
		observers.erase(std::remove_if(begin(observers), end(observers), isEqualTo(observerToRemove)));
	}

protected:
	void notifyAllObservers() const{
		for (const auto &observer : observers){
			observer->update();
		}
	}

private:
	std::vector<ObserverPtr> observers;
};





class SpreadSheetModel : public Subject{
public:
	void setCellValue(std::string_view col, const int row, const double val){
		std::cout << "Cell [" << col << "," << row <<"] = " << val << std::endl;
		notifyAllObservers();
	}
};



class TableView : public Observer{
public:
	 TableView (SpreadSheetModel & sModel) : model {sModel}{
		;
	}


	 int getId() override{
		 return 1;
	 }
	 void update() override {
		 std::cout<<"Table view updated"<<std::endl;
	 }

private:
	 SpreadSheetModel model;
};





class BarChartView : public Observer{
public:
	 BarChartView (SpreadSheetModel & sModel) : model {sModel}{
		;
	}


	 int getId() override{
		 return 2;
	 }
	 void update() override {
		 std::cout<<"Bar chart view updated"<<std::endl;
	 }

private:
	 SpreadSheetModel model;
};



class PieChartView : public Observer{
public:
	 PieChartView (SpreadSheetModel & sModel) : model {sModel}{
		;
	}

	 int getId() override{
		 return 3;
	 }
	 void update() override {
		 std::cout<<"Pie chart view updated"<<std::endl;
	 }

private:
	 SpreadSheetModel model;
};





int main(void){

	SpreadSheetModel spreadSheetModel{};

	ObserverPtr observer2 = std::make_shared<BarChartView>(spreadSheetModel);
	spreadSheetModel.addObserver(observer2);

	ObserverPtr observer3 = std::make_shared<PieChartView>(spreadSheetModel);
	spreadSheetModel.addObserver(observer3);

	spreadSheetModel.setCellValue("a", 2, 100);


}



