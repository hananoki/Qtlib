#pragma once
#include <QtConcurrent>
#include <QtConcurrent/QtConcurrentRun>

//////////////////////////////////////////////////////////////////////////////////
template< class T >
class HWorker {
public:
	QFuture<void> future;
	QFutureWatcher<void> watcher;
	bool workerExit = false;
	bool cancelQueue = false;

	QMutex mutexRequest;
	QQueue<T> _queue;
	QWaitCondition condRequest;

	/////////////////////////////////////////
	void startWorker() {
		future = QtConcurrent::run( [&]() {
			while( !workerExit ) {
				T req;
				{
					QMutexLocker _( &mutexRequest );
					while( _queue.isEmpty() ) {
						watcher.finished();
						if( cancelQueue ) {
							cancelQueue = false;
						}
						//emit self->progressEnd();
						condRequest.wait( &mutexRequest );
						if( workerExit )return;
					}
					req = _queue.dequeue();
					if( cancelQueue )continue;
				}
				handleWorker( req );
			}
		} );
		watcher.setFuture( future );
	}


	/////////////////////////////////////////
	void setCancelQueue() {
		QMutexLocker _( &mutexRequest );
		cancelQueue = true;
		condRequest.wakeAll();
	}


	/////////////////////////////////////////
	void addRequest( const T& requestData ) {
		QMutexLocker _( &mutexRequest );
		_queue.enqueue( requestData );
		condRequest.wakeAll();
	}


	/////////////////////////////////////////
	virtual void handleWorker( const T& data ) = 0;
};

