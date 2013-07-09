
modes
=====
Interactive vs explicit

explicit mode fails if you don't provide all the parameters required.
interactive mode uses text ui to gather extra info

explicit uses console like output for displaying info/progress
interactive uses text ui for output

> egg switch<ret>
Missing branch name...
  branch1
* branch2 *
  master
>

> egg switch<ret>
Which branch?
  branch1
=>branch2<=
  branch3
<process arrow keys, (process other keys), wait for ret, then switch branchs>
Which branch?
 >branch1<
= branch2 =
  branch3

 
 
egg command --sub <=>  egg command-sub


references (simple)
==========
branch
remote-branch
tag


branchs       remotes            tags
========      ===============    ====
feature1					; local feature
feature2  ->  origin/feature2			; local tracking remote
              origin/feature3			; published but no local
                                 tag1		; tag - detached HEAD
feature4  ->  origin/something
feature5  ->  origin/feature5,alt/feature5	; multiple upstream repos



commit on detached HEAD should ask to make new local branch


egg init
========
egg init [--template NAME] [REPONAME]

if REPONAME doesn't exist create it.
if not specified use ./

if REPODIR is already a git repo warn and do nothing

copy files from template and set up .git repo




egg clone
=========
egg clone REPO_URL [DIR]




egg status
==========
egg status [--prompt]

 


egg stage/unstage
=================
egg stage FILE+
egg stage --all
egg stage --rm FILE+		same as egg rm FILE+
egg unstage FILE+




egg revert
==========
egg revert FILE*
egg revert --rollback REVISION|CHECKPOINT




egg switch
==========
egg switch NAME




egg commit
==========
egg commit [--msg STRING]





CHECKPOINT ::= branch name, commit id, tag


egg branch [--stash] NEWNAME [CHECKPOINT]
egg branch --delete NAME
egg branch --move NEWNAME [CHECKPOINT]
egg branch --rename|--rebase
egg branch --pull NEWNAME REPOURL
egg branch --remote URL

egg remote

egg push

egg pull

egg merge FROMBRANCH
egg mergein ... --squash

egg diff [--staged] [FILE*]

egg rebase --against BRANCH

egg log

egg stash [ident]
egg unstash [ident]
egg stash --apply [ident]
egg stash --drop [ident]

egg cherry-pick
egg mergetool

egg serve

egg reset    // like git clean





git log --graph --pretty=format:'%C(yellow)%h%Creset%C(blue)%d%Creset %C(white bold)%s%Creset %C(white dim)(by %an %ar)%Creset' --all

git log --graph --simplify-by-decoration --pretty=format:'%d' --all


git checkout master
git merge --squash private_feature_branch


git checkout -b myfeature develop

git checkout develop ; git merge --no-ff myfeature

git branch -d myfeature






       A revision parameter <rev> typically, but not necessarily, names a commit object.
       It uses what is called an extended SHA1 syntax. Here are various ways to spell
       object names. The ones listed near the end of this list name trees and blobs
       contained in a commit.

       <sha1>, e.g. dae86e1950b1277e545cee180551750029cfe735, dae86e
           The full SHA1 object name (40-byte hexadecimal string), or a leading substring
           that is unique within the repository. E.g.
           dae86e1950b1277e545cee180551750029cfe735 and dae86e both name the same commit
           object if there is no other object in your repository whose object name starts
           with dae86e.

       <describeOutput>, e.g. v1.7.4.2-679-g3bee7fb
           Output from git describe; i.e. a closest tag, optionally followed by a dash and
           a number of commits, followed by a dash, a g, and an abbreviated object name.

       <refname>, e.g. master, heads/master, refs/heads/master
           A symbolic ref name. E.g.  master typically means the commit object referenced
           by refs/heads/master. If you happen to have both heads/master and tags/master,
           you can explicitly say heads/master to tell git which one you mean. When
           ambiguous, a <name> is disambiguated by taking the first match in the following
           rules:

            1. If $GIT_DIR/<name> exists, that is what you mean (this is usually useful
               only for HEAD, FETCH_HEAD, ORIG_HEAD, MERGE_HEAD and CHERRY_PICK_HEAD);

            2. otherwise, refs/<name> if it exists;

            3. otherwise, refs/tags/<refname> if it exists;

            4. otherwise, refs/heads/<name> if it exists;

            5. otherwise, refs/remotes/<name> if it exists;

            6. otherwise, refs/remotes/<name>/HEAD if it exists.

               HEAD names the commit on which you based the changes in the working tree.
               FETCH_HEAD records the branch which you fetched from a remote repository
               with your last git fetch invocation.  ORIG_HEAD is created by commands that
               move your HEAD in a drastic way, to record the position of the HEAD before
               their operation, so that you can easily change the tip of the branch back
               to the state before you ran them.  MERGE_HEAD records the commit(s) which
               you are merging into your branch when you run git merge.  CHERRY_PICK_HEAD
               records the commit which you are cherry-picking when you run git
               cherry-pick.

               Note that any of the refs/* cases above may come either from the
               $GIT_DIR/refs directory or from the $GIT_DIR/packed-refs file.
               
       <refname>@{<date>}, e.g. master@{yesterday}, HEAD@{5 minutes ago}
           A ref followed by the suffix @ with a date specification enclosed in a brace
           pair (e.g.  {yesterday}, {1 month 2 weeks 3 days 1 hour 1 second ago} or
           {1979-02-26 18:30:00}) specifies the value of the ref at a prior point in time.
           This suffix may only be used immediately following a ref name and the ref must
           have an existing log ($GIT_DIR/logs/<ref>). Note that this looks up the state
           of your local ref at a given time; e.g., what was in your local master branch
           last week. If you want to look at commits made during certain times, see
           --since and --until.

       <refname>@{<n>}, e.g. master@{1}
           A ref followed by the suffix @ with an ordinal specification enclosed in a
           brace pair (e.g.  {1}, {15}) specifies the n-th prior value of that ref. For
           example master@{1} is the immediate prior value of master while master@{5} is
           the 5th prior value of master. This suffix may only be used immediately
           following a ref name and the ref must have an existing log
           ($GIT_DIR/logs/<refname>).

       @{<n>}, e.g. @{1}
           You can use the @ construct with an empty ref part to get at a reflog entry of
           the current branch. For example, if you are on branch blabla then @{1} means
           the same as blabla@{1}.

       @{-<n>}, e.g. @{-1}
           The construct @{-<n>} means the <n>th branch checked out before the current
           one.

       <refname>@{upstream}, e.g. master@{upstream}, @{u}
           The suffix @{upstream} to a ref (short form <refname>@{u}) refers to the branch
           the ref is set to build on top of. A missing ref defaults to the current
           branch.

       <rev>^, e.g. HEAD^, v1.5.1^0
           A suffix ^ to a revision parameter means the first parent of that commit
           object.  ^<n> means the <n>th parent (i.e.  <rev>^ is equivalent to <rev>^1).
           As a special rule, <rev>^0 means the commit itself and is used when <rev> is
           the object name of a tag object that refers to a commit object.

       <rev>~<n>, e.g. master~3
           A suffix ~<n> to a revision parameter means the commit object that is the <n>th
           generation ancestor of the named commit object, following only the first
           parents. I.e.  <rev>~3 is equivalent to <rev>^^^ which is equivalent to
           <rev>^1^1^1. See below for an illustration of the usage of this form.

       <rev>^{<type>}, e.g. v0.99.8^{commit}
           A suffix ^ followed by an object type name enclosed in brace pair means the
           object could be a tag, and dereference the tag recursively until an object of
           that type is found or the object cannot be dereferenced anymore (in which case,
           barf).  <rev>^0 is a short-hand for <rev>^{commit}.
           
       <rev>^{/<text>}, e.g. HEAD^{/fix nasty bug}
           A suffix ^ to a revision parameter, followed by a brace pair that contains a
           text led by a slash, is the same as the :/fix nasty bug syntax below except
           that it returns the youngest matching commit which is reachable from the <rev>
           before ^.

       :/<text>, e.g. :/fix nasty bug
           A colon, followed by a slash, followed by a text, names a commit whose commit
           message matches the specified regular expression. This name returns the
           youngest matching commit which is reachable from any ref. If the commit message
           starts with a !  you have to repeat that; the special sequence :/!, followed by
           something else than !, is reserved for now. The regular expression can match
           any part of the commit message. To match messages starting with a string, one
           can use e.g.  :/^foo.

       <rev>:<path>, e.g. HEAD:README, :README, master:./README
           A suffix : followed by a path names the blob or tree at the given path in the
           tree-ish object named by the part before the colon.  :path (with an empty part
           before the colon) is a special case of the syntax described next: content
           recorded in the index at the given path. A path starting with ./ or ../ is
           relative to the current working directory. The given path will be converted to
           be relative to the working tree’s root directory. This is most useful to
           address a blob or tree from a commit or tree that has the same tree structure
           as the working tree.

       :<n>:<path>, e.g. :0:README, :README
           A colon, optionally followed by a stage number (0 to 3) and a colon, followed
           by a path, names a blob object in the index at the given path. A missing stage
           number (and the colon that follows it) names a stage 0 entry. During a merge,
           stage 1 is the common ancestor, stage 2 is the target branch’s version
           (typically the current branch), and stage 3 is the version from the branch
           which is being merged.



Git lets you ignore those files by assuming they are unchanged. This is done by running the git update-index --assume-unchanged path/to/file.txt command. Once marking a file as such, git will completely ignore any changes on that file; they will not show up when running git status or git diff, nor will they ever be committed.

To make git track the file again, simply run git update-index --no-assume-unchanged path/to/file.txt.



workflow interactions between stash and pull,


git pull
"have changes blah blah"
git stash
git pull
git stash pop
"have conflicts"

-- stash hasn't been dropped
-- need to do git add to stage files to resolve conflicts even tho you're not commiting yet



