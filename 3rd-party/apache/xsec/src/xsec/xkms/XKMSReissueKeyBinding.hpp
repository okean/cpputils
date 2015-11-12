/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * XSEC
 *
 * XKMSRevokeKeyBinding := Interface for KeyBinding elements
 *
 * $Id$
 *
 */

#ifndef XKMSREISSUEKEYBINDING_INCLUDE
#define XKMSREISSUEKEYBINDING_INCLUDE

// XSEC Includes

#include <xsec/framework/XSECDefs.hpp>
#include <xsec/xkms/XKMSKeyBindingAbstractType.hpp>

/**
 * @ingroup xkms
 */

/**
 * @brief Interface definition for the ReissueKeyBinding elements
 *
 * The \<ReissueKeyBinding\> Element is used in a request to reissue
 * a particular key from an XKRS service
 *
 * The schema definition for ReissueKeyBinding is as follows :
 *
 * \verbatim
   <!-- ReissueKeyBinding -->
	<element name="ReissueKeyBinding" type="xkms:KeyBindingType"/>
   <!-- /ReissueKeyBinding -->
 \endverbatim
 */

class XKMSStatus;

class XKMSReissueKeyBinding : public XKMSKeyBindingAbstractType {

	/** @name Constructors and Destructors */
	//@{

protected:

	XKMSReissueKeyBinding() {};

public:

	virtual ~XKMSReissueKeyBinding() {};

	//@}

	/** @name Status handling */
	//@{

	/**
	 * \brief Obtain the status element for this KeyBinding
	 *
	 * The \<Status\> element is used to describe to the caller the
	 * validity of they key being described.  This call is used to
	 * obtain the status element
	 *
	 * @return A pointer to the XKMSStatus element
	 */

	virtual XKMSStatus * getStatus(void) const = 0;

	//@}

private:

	// Unimplemented
	XKMSReissueKeyBinding(const XKMSReissueKeyBinding &);
	XKMSReissueKeyBinding & operator = (const XKMSReissueKeyBinding &);

};

#endif /* XKMSREISSUEKEYBINDING_INCLUDE */
