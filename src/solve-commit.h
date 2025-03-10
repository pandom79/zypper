/*---------------------------------------------------------------------------*\
                          ____  _ _ __ _ __  ___ _ _
                         |_ / || | '_ \ '_ \/ -_) '_|
                         /__|\_, | .__/ .__/\___|_|
                             |__/|_|  |_|
\*---------------------------------------------------------------------------*/

/**
 * Solve and commit code.
 *
 * This part is responsible for calling the solver, feeding the result back
 * to the user in form of dependency problem dialogue and installation summary,
 * and calling commit to do actually do what has been written in the summary. 
 */
#ifndef SOLVE_COMMIT_H_
#define SOLVE_COMMIT_H_

#include "Zypper.h"
#include "Summary.h"

/**
 * Run the solver.
 * 
 * \return <tt>true</tt> if a solution has been found, <tt>false</tt> otherwise 
 */
bool resolve(Zypper & zypper);


struct SolveAndCommitPolicy {

  SolveAndCommitPolicy();

  /*!
  * Usually \ref solve_and_commit only executes a commit if packages need to
  * be installed or removed. With \a ForceCommit a commit is always executed.
  */
  bool forceCommit () const;
  SolveAndCommitPolicy &forceCommit ( bool enable );

  /*!
   * Changes the amount of information included by the summary
   */
  const Summary::ViewOptions &summaryOptions () const;
  SolveAndCommitPolicy &summaryOptions ( Summary::ViewOptions options );

  ZYppCommitPolicy &zyppCommitPolicy ();
  const ZYppCommitPolicy &zyppCommitPolicy () const;
  SolveAndCommitPolicy &zyppCommitPolicy ( ZYppCommitPolicy policy );

  SolveAndCommitPolicy &downloadMode(DownloadMode dlMode);
  DownloadMode downloadMode() const;

private:
  bool _forceCommit    = false;
  Summary::ViewOptions _summaryOptions = Summary::DEFAULT;
  ZYppCommitPolicy _zyppCommitPolicy;
};

/**
 * Runs solver on the pool, asks to choose solution of eventual problems
 * (when run interactively) and commits the result.
 *
 * \param have_extra_deps ?
 * \return ZYPPER_EXIT_INF_REBOOT_NEEDED, ZYPPER_EXIT_INF_RESTART_NEEDED,
 *         or ZYPPER_EXIT_OK or ZYPPER_EXIT_ERR_ZYPP on zypp error.
 *
 */
void solve_and_commit( Zypper &zypper, SolveAndCommitPolicy policy );


#endif /*SOLVE_COMMIT_H_*/
