#ifndef _E_MSG_QUEUE_H_
#define _E_MSG_QUEUE_H_

#include <mutex>
#include <memory>
#include <list>

#include "EMsg.h"

namespace Eg {

	class EMsgQueue;

	typedef std::shared_ptr<EMsgQueue> EMsgQueuePtr;

	// Only new it
	class EMsgQueue {
		std::mutex lock;
		std::list<EMsgBase*> msg;

		EMsgQueue() {}
	public:
		static EMsgQueuePtr create() {
			return EMsgQueuePtr(new EMsgQueue());
		}
		void put(EMsgBase* m) {
			std::unique_lock<std::mutex> locker(lock);
			msg.push_back(m);
		}
		void get(std::list<EMsgBase*>& lst) {
			std::unique_lock<std::mutex> locker(lock);
			lst.swap(msg);
		}
	};

}

#endif