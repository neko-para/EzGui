#ifndef _E_SIGNAL_H_
#define _E_SIGNAL_H_

#include <functional>
#include <vector>

namespace Eg {

	template <typename... Types>
	class Tuple;

	template <>
	class Tuple<> {
	public:
		void call(std::function<void(void)> func) const {
			func();
		}
	};

	template <typename T, typename... Types>
	class Tuple<T, Types...> : public Tuple<Types...> {
		typedef Tuple<Types...> base;
	protected:
		T data;
	public:
		Tuple(const T& t, const Types&... ex) : base(ex...), data(t) {}

		template <typename... Arg>
		void call(std::function<void(Arg...)> func, const Arg&... arg) const {
			func(arg...);
		}

		template <typename... Arg, typename... CurArg>
		void call(std::function<void(Arg...)> func, const CurArg&... arg) const {
			((base*)this)->call(func, arg..., data);
		}
	};

	template <typename T>
	class Tuple<T> : public Tuple<> {
	protected:
		T data;
	public:
		Tuple(const T& t) : data(t) {}

		template <typename... Arg>
		void call(std::function<void(Arg...)> func, const Arg&... arg) const {
			func(arg...);
		}

		void call(std::function<void(T)> func) const {
			func(data);
		}
	};

	template <typename... Arg>
	struct ConnectionBase {
		virtual void* slot() const = 0;
		virtual void call(const Tuple<Arg...>& tuple) = 0;
	};

	template <>
	struct ConnectionBase<void> {
		virtual void* slot() const = 0;
		virtual void call() = 0;
	};

	template <typename... Types>
	class Signal;

	template <typename Slt, typename... Arg>
	class Connection : public ConnectionBase<Arg...> {
		Signal<Arg...>* signal;
		Slt* slt;
	public:
		Connection(Signal<Arg...>* s, Slt* f) : signal(s), slt(f) {}
		virtual void call(const Tuple<Arg...>& tuple) {
			tuple.call(typename Slt::function(*slt));
		}
		virtual void* slot() const {
			return slt;
		}
		void disconnect();
	};

	
	template <typename Slt>
	class Connection<Slt, void> : public ConnectionBase<void> {
		Signal<void>* signal;
		Slt* slt;
	public:
		Connection(Signal<void>* s, Slt* f) : signal(s), slt(f) {}
		virtual void call() {
			(*slt)();
		}
		virtual void* slot() const {
			return slt;
		}
		void disconnect();
	};

	template <typename... Types>
	class Slot {
	public:
		typedef std::function<void(Types...)> function;
	private:
		function func;
	public:
		Slot(std::function<void(Types...)> f) : func(f) {}
		void operator()(Types... arg) {
			func(arg...);
		}
	};

	template <>
	class Slot<void> {
	public:
		typedef std::function<void(void)> function;
	private:
		function func;
	public:
		Slot(std::function<void(void)> f) : func(f) {}
		void operator()() {
			func();
		}
	};

	template <typename... Types>
	class Signal {
		std::vector<ConnectionBase<Types...>*> connections;
	public:
		template <typename... Slt>
		Connection<Slot<Slt...>, Types...> connect(Slot<Slt...>& slt) {
			typedef Connection<Slot<Slt...>, Types...> ThisConnection;
			ThisConnection* p = new ThisConnection(this, &slt);
			connections.push_back(p);
			return *p;
		}
		template <typename... Slt>
		void disconnect(Slot<Slt...>* p) {
			for (auto it = connections.begin(); it != connections.end(); ++it) {
				if ((*it)->slot() == p) {
					delete *it;
					connections.erase(it);
					break;
				}
			}
		}
		void emit(const Types&... arg) {
			Tuple<Types...> data(arg...);
			for (auto p : connections) {
				p->call(data);
			}
		}
	};

	template <>
	class Signal<void> {
		std::vector<ConnectionBase<void>*> connections;
	public:
		template <typename... Slt>
		Connection<Slot<Slt...>, void> connect(Slot<Slt...>& slt) {
			typedef Connection<Slot<Slt...>, void> ThisConnection;
			ThisConnection* p = new ThisConnection(this, &slt);
			connections.push_back(p);
			return *p;
		}
		template <typename... Slt>
		void disconnect(Slot<Slt...>* p) {
			for (auto it = connections.begin(); it != connections.end(); ++it) {
				if ((*it)->slot() == p) {
					delete *it;
					connections.erase(it);
					break;
				}
			}
		}
		void emit() {
			for (auto p : connections) {
				p->call();
			}
		}
	};

	template <typename... Arg>
	class TransferSlot {
		Signal<Arg...>& signal;
	public:
		typedef std::function<void(Arg...)> function;

		TransferSlot(Signal<Arg...>& sig) : signal(sig) {}

		void operator()(Arg... arg) {
			signal.emit(arg...);
		}
	};

	template <>
	class TransferSlot<void> {
		Signal<void>& signal;
	public:
		typedef std::function<void(void)> function;

		TransferSlot(Signal<void>& sig) : signal(sig) {}

		void operator()() {
			signal.emit();
		}
	};

	template <typename Slt, typename... Sig>
	inline void Connection<Slt, Sig...>::disconnect() {
		signal->disconnect(slt);
	}

	template <typename Slt>
	inline void Connection<Slt, void>::disconnect() {
		signal->disconnect(slt);
	}

}

#endif