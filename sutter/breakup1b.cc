// Example 1(b): Using a continuation style,
// and adding resilience to collection changes
//
class LongOperation : public Message {
	Collection myItems;
	int start;
	LongHelper helper;
public:
	LongOperation(
	int start_ = 0,
	LongHelper helper_ = nullptr,
	Collection myItems = nullptr
	)
	: start(start_),
	helper(helper_),
	myItems(myItems_)
	{ }
	void run() {
		if( helper == nullptr ) {// if first time through
			helper = GetHelper(); // get helper
			myItems = items.copy();// and take a snapshot of items
		}
		int i = 0; // do just another chunk's worth
		for( ; i < ChunkSize && start+i < myItems.size(); ++i ) {
			helper->render( myItems[ start+i ] );
		}
		if( start+i < myItems</font>.size() ) // if not done,
		// launch a continuation
		queue.push( LongOperation( start+i, helper, myItems ) );
		else { // if last time through, finish up
			helper->print();
			Free( myItems ); // and clean up myItems
		}
	}
}