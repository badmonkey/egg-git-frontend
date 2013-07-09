
#include <list>
#include <iostream>
#include "git2.h"



int callback(const char *branch_name,
	     git_branch_t branch_type,
	     void *payload)
{
  std::cout << "BRANCH "
	    << (branch_type == GIT_BRANCH_REMOTE ? "R " : "")
            << branch_name
            << std::endl;
  return 0;
} // callback()



int main(int argc, char** argv)
{
  git_repository*  repo = NULL;
  
  git_repository_open(&repo, "./");

  
  git_branch_foreach(repo, GIT_BRANCH_LOCAL|GIT_BRANCH_REMOTE, callback, NULL);
 
  
  git_reference* HEADref = NULL;
  
  git_repository_head(&HEADref, repo);
  
  const char* HEAD_name = git_reference_name(HEADref);
  const char* head_name_ptr;
  
  git_branch_name(&head_name_ptr, HEADref);
  
  std::cout << "HEAD "
	    << ( git_reference_is_branch(HEADref) ? "branch " : "?? " )
	    << HEAD_name
	    << "  =>  "
	    << head_name_ptr
	    << std::endl;
	    
  
  

  char REMOTE_name[128];
   
  git_branch_tracking_name(REMOTE_name, 128, repo, HEAD_name);
	    
  git_reference* TRACKref = NULL;
  
  git_branch_tracking(&TRACKref, HEADref);
  const char* name_ptr;
  
  git_branch_name(&name_ptr, TRACKref);
  
  std::cout << "HEAD tracking " << git_reference_name(TRACKref) << "  =>  " <<  name_ptr << std::endl;
  

  git_reference* localref = NULL;
  git_reference* remoteref = NULL;
  
  std::cout << "LOOKUP local " << git_branch_lookup(&localref, repo, head_name_ptr, GIT_BRANCH_LOCAL) << std::endl;
  std::cout << "LOOKUP remote " << git_branch_lookup(&remoteref, repo, name_ptr, GIT_BRANCH_REMOTE) << std::endl;
  
  
  size_t ahead = 0;
  size_t behind = 0;
  
  if ( git_reference_type(localref) != GIT_REF_OID)
  {
    std::cout << "REF local is NOT oid" << std::endl;
  }
  
  if ( git_reference_type(remoteref) != GIT_REF_OID)
  {
    std::cout << "REF remote is NOT oid" << std::endl;
  }
  
  
  git_graph_ahead_behind(&ahead, &behind, repo, git_reference_target(localref), git_reference_target(remoteref) );
  
  std::cout << "GRAPH "
	    << ahead << " ahead, "
	    << behind << " behind"
	    << std::endl;

	    

  git_strarray ref_list;
  git_reference_list(&ref_list, repo, GIT_REF_LISTALL);

  const char *refname;
  git_reference *ref;

  // Now that we have the list of reference names, we can lookup each ref one at a time and
  // resolve them to the SHA, then print both values out.
  for (int i = 0; i < ref_list.count; ++i)
  {
    refname = ref_list.strings[i];
    git_reference_lookup(&ref, repo, refname);

    switch (git_reference_type(ref))
    {
    case GIT_REF_OID:
      //char out[41];
      //git_oid_fmt(out, git_reference_target(ref));
      //std::cout << refname << " [" << out << "]" << std::endl;
      const char* name_ptr;
  
      git_branch_name(&name_ptr, ref);
  
      std::cout << "REF " << refname << " =>> " << name_ptr << std::endl;
      break;

    case GIT_REF_SYMBOLIC:
      std::cout << "REF " << refname << " => " << git_reference_symbolic_target(ref) << std::endl;
      
      break;
      
    default:
      std::cerr << "Unexpected reference type\n";
      exit(1);
    }
  }

  git_strarray_free(&ref_list);

  
  git_repository_free(repo);

  return 0;
}