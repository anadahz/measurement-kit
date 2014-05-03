/* libneubot/libneubot.cpp */

/*-
 * Copyright (c) 2013-2014
 *     Nexa Center for Internet & Society, Politecnico di Torino (DAUIN)
 *     and Simone Basso <bassosimone@gmail.com>.
 *
 * This file is part of Neubot <http://www.neubot.org/>.
 *
 * Neubot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Neubot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Neubot.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// Libneubot C wrappers for C++
//
// Ideally this file should be as much autogenerated as possible
//

#include <new>
#include <stdlib.h>

#include <event2/event.h>

#include "neubot.h"
#include "log.h"

#include "pollable.hh"

//
// Pollable
//

struct NeubotPollable : public Neubot::Pollable {

	neubot_slot_vo on_handle_error;
	neubot_slot_vo on_handle_read;
	neubot_slot_vo on_handle_write;
	void *opaque;

	NeubotPollable(NeubotPoller *poller, neubot_slot_vo on_read,
	    neubot_slot_vo on_write, neubot_slot_vo on_error,
	    void *opaque) : Neubot::Pollable(poller) {
		neubot_info("NeubotPollable::construct");
		this->on_handle_error = on_error;
		this->on_handle_read = on_read;
		this->on_handle_write = on_write;
		this->opaque = opaque;
	};

	virtual void handle_read(void) {
		neubot_info("NeubotPollable::handle_read");
		this->on_handle_read(this->opaque);
	};

	virtual void handle_write(void) {
		neubot_info("NeubotPollable::handle_write");
		this->on_handle_write(this->opaque);
	};

	virtual void handle_error(void) {
		neubot_info("NeubotPollable::handle_error");
		this->on_handle_error(this->opaque);
	};

	virtual ~NeubotPollable(void) {
		neubot_info("NeubotPollable::~NeubotPollable");
	};
};

NeubotPollable *
NeubotPollable_construct(NeubotPoller *poller, neubot_slot_vo handle_read,
    neubot_slot_vo handle_write, neubot_slot_vo handle_error,
    void *opaque)
{
	if (poller == NULL)
		abort();

	try {
		return (new NeubotPollable(poller, handle_read, handle_write,
		    handle_error, opaque));
	} catch (...) {
		return (NULL);
	}
}

int
NeubotPollable_attach(NeubotPollable *self, long long fileno)
{
	if (self == NULL)
		abort();

	return (self->attach(fileno));
}

void
NeubotPollable_detach(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	self->detach();
}

long long
NeubotPollable_get_fileno(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	return (self->get_fileno());
}

int
NeubotPollable_set_readable(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	return (self->set_readable());
}

int
NeubotPollable_unset_readable(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	return (self->unset_readable());
}

int
NeubotPollable_set_writable(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	return (self->set_writable());
}

int
NeubotPollable_unset_writable(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	return (self->unset_writable());
}

void
NeubotPollable_set_timeout(NeubotPollable *self, double timeout)
{
	if (self == NULL)
		abort();

	self->set_timeout(timeout);
}

void
NeubotPollable_clear_timeout(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	self->clear_timeout();
}

void
NeubotPollable_close(NeubotPollable *self)
{
	if (self == NULL)
		abort();

	delete (self);
}
