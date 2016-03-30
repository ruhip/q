/*
 * Copyright 2016 Gustaf Räntilä
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBQIO_SOCKET_EVENT_HPP
#define LIBQIO_SOCKET_EVENT_HPP

#include <q-io/types.hpp>
#include <q-io/event.hpp>

namespace q { namespace io {

/**
 * The socket_event class represents an event for a socket, and must be sub-
 * classed.
 */
class socket_event
: public event
{
public:
	~socket_event( );

protected:
	socket_event( socket_t );

	void detect_readability( );
	void detect_writability( );

	virtual socket_event_ptr socket_event_shared_from_this( ) = 0;

	virtual void on_event_read( ) noexcept override = 0;
	virtual void on_event_write( ) noexcept override = 0;

	socket_t socket( ) const;

private:
	friend class dispatcher;
	friend class server_socket;

	void sub_attach( const dispatcher_ptr& dispatcher ) noexcept override;

	void close_socket( );

	struct pimpl;
	std::unique_ptr< pimpl > pimpl_;
};

} } // namespace io, namespace q

#endif // LIBQIO_SOCKET_EVENT_HPP