// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                   OpenMS Mass Spectrometry Framework
// --------------------------------------------------------------------------
//  Copyright (C) 2003-2006 -- Oliver Kohlbacher, Knut Reinert
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Maintainer: Martin Langwisch $
// --------------------------------------------------------------------------

#ifndef OPENMS_FORMAT_SEQUESTOUTFILE_H
#define OPENMS_FORMAT_SEQUESTOUTFILE_H

#include <OpenMS/KERNEL/KernelTraits.h>
#include <OpenMS/METADATA/Identification.h>
#include <OpenMS/METADATA/ProteinIdentification.h>
#include <OpenMS/METADATA/PeptideHit.h>
#include <OpenMS/METADATA/ProteinHit.h>
#include <OpenMS/DATASTRUCTURES/Date.h>
#include <OpenMS/CONCEPT/Types.h>
#include <OpenMS/FORMAT/FASTAFile.h>
#include <OpenMS/DATASTRUCTURES/String.h>

#include <iostream>
#include <fstream>
#include <string>

namespace OpenMS
{
  /**
    @brief Representation of an Sequest outfile
    
    This class serves to read in an Sequest outfile. The information can be 
    retrieved via the >> operator. 
		
	@todo move split to String, check whether every getline may throw an exception, better solution where to add ensurePathChar, what to do when sequences cannot be found (right now: return empty sequence)
  
  	@ingroup FileIO
  */
  class SequestOutfile
  {
    public:
      // Constructor
      SequestOutfile();
			
			SequestOutfile(const SequestOutfile& sequest_outfile);
			
			// destructor
			//virtual ~SequestOutfile();

			// assignment operator
			SequestOutfile& operator=(const SequestOutfile& sequest_outfile);
			
			void load(const std::string& result_filename, std::vector< Identification >&	identifications, ProteinIdentification&	protein_identification, std::vector< float >& precursor_retention_times, std::vector< float >& precursor_mz_values, const double& p_value_threshold, const std::string& database = "", const std::string& snd_database = "") throw (Exception::FileNotFound, Exception::ParseError);
			
		protected:
			// split a string into substrings using splitter
			bool split(const String& s, const String& splitter, std::vector<String>& substrings);
			
			// retrieve columns from a Sequest Outfile line
			bool getColumns(std::ifstream& result_file, std::vector< String >& substrings, const std::string& result_filename);
			
			// retrieve sequences from a FASTA database
			void getSequences(const String& database_filename, std::map< String, unsigned int > ac_position_map, std::vector< String >& sequences, std::vector< std::pair< String, unsigned int > >& found, std::map< String, unsigned int >& not_found) throw (Exception::FileNotFound);
			
			void getACAndACType(String line, std::string& accession, std::string& accession_type) throw (Exception::ParseError);
			
			bool updatePeptideHits(PeptideHit& peptide_hit, std::vector< PeptideHit >& peptide_hits);
			
			void getPrecursorRTandMZ(const std::vector< std::pair< String, std::vector< unsigned int > > >& files_and_scan_numbers, std::vector< float >&  precursor_retention_times, std::vector< float >& precursor_mz_values);
			
			// make sure there's a char marking the string as directory
			void ensurePathChar(std::string& path, char path_char = '/');
			
			std::string pathDir(const std::string& filename, char slash = '/');
			
			std::string fileName(const std::string& filename, char slash = '/');
   };
	
} //namespace OpenMS

#endif // OPENMS_FORMAT_SEQUESTOUTFILE_H
