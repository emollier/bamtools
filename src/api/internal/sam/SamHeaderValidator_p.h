// ***************************************************************************
// SamHeaderValidator.h (c) 2010 Derek Barnett
// Marth Lab, Department of Biology, Boston College
// ---------------------------------------------------------------------------
// Last modified: 6 October 2011 (DB)
// ---------------------------------------------------------------------------
// Provides functionality for validating SamHeader data
// ***************************************************************************

#ifndef SAM_HEADER_VALIDATOR_P_H
#define SAM_HEADER_VALIDATOR_P_H

#include "api/api_global.h"

//  -------------
//  W A R N I N G
//  -------------
//
// This file is not part of the BamTools API.  It exists purely as an
// implementation detail. This header file may change from version to version
// without notice, or even be removed.
//
// We mean it.

#include <iostream>
#include <string>
#include <vector>

namespace BamTools {

struct SamHeader;
struct SamReadGroup;
struct SamSequence;

namespace Internal {

class API_NO_EXPORT SamHeaderValidator
{

    // ctor & dtor
public:
    SamHeaderValidator(const SamHeader& header);

    // SamHeaderValidator interface
public:
    // prints error & warning messages
    void PrintMessages(std::ostream& stream);

    // validates SamHeader data, returns true/false accordingly
    bool Validate();

    // internal methods
private:
    // validate header metadata
    bool ValidateMetadata();
    bool ValidateVersion();
    bool ContainsOnlyDigits(const std::string& s);
    bool ValidateSortOrder();
    bool ValidateGroupOrder();

    // validate sequence dictionary
    bool ValidateSequenceDictionary();
    bool ContainsUniqueSequenceNames();
    bool CheckNameFormat(const std::string& name);
    bool ValidateSequence(const SamSequence& seq);
    bool CheckLengthInRange(const std::string& length);

    // validate read group dictionary
    bool ValidateReadGroupDictionary();
    bool ContainsUniqueIDsAndPlatformUnits();
    bool ValidateReadGroup(const SamReadGroup& rg);
    bool CheckReadGroupID(const std::string& id);
    bool CheckSequencingTechnology(const std::string& technology);

    // validate program data
    bool ValidateProgramChain();
    bool ContainsUniqueProgramIds();
    bool ValidatePreviousProgramIds();

    // error reporting
    void AddError(const std::string& message);
    void AddWarning(const std::string& message);
    void PrintErrorMessages(std::ostream& stream);
    void PrintWarningMessages(std::ostream& stream);

    // data members
private:
    // SamHeader being validated
    const SamHeader& m_header;

    // error reporting helpers
    static const std::string ERROR_PREFIX;
    static const std::string WARN_PREFIX;
    static const std::string NEWLINE;

    // error reporting messages
    std::vector<std::string> m_errorMessages;
    std::vector<std::string> m_warningMessages;
};

}  // namespace Internal
}  // namespace BamTools

#endif  // SAM_HEADER_VALIDATOR_P_H
