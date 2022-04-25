// Example 1(a): Using a continuation style
//
class LongOperation : public Message {
	int start;
	LongHelper helper;
public:
	LongOperation( int start_ = 0,	LongHelper *helper_ = nullptr )
		: start(start_), helper(helper_) { }
	void run() {
		if( helper == nullptr)
			// if first time through, get helper</font>
			helper = GetHelper();
		int i = 0;
		
		// do just another chunk's worth</font>
		for( ; i < ChunkSize && start+i < items.size(); ++i ) {
			helper->render( items[ start+i ] );
		}

		if( start+i < items.size() )
		// if not done, launch a continuation
		queue.push(LongOperation(start+i, helper));
		else
		// if last time through, finish up
		helper->print();
	}
}