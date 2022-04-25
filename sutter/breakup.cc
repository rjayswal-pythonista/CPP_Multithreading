// An idealized thread mainline
//
do {
    message = queue.pop() // get the message
                          // (might wait)
    message->run();    // and execute it
} while( !done );         // check for exit

// A simplified message type to accomplish some
// long operation
//
class LongOperation : public Message {
public:
   void run() {
      LongHelper helper = GetHelper();
// issue: what if this loop could take a long time?
   for( int i = 0; i < items.size(); ++i ) {
      helper->render( items[i] );
   }
   helper->print();
 }
}